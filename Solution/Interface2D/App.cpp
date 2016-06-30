#include "App.h"
#include "Powerplant.h"
#include "Map.h"
#include "UnitMap.h"
#include "Line.h"
#include "Chargers.h"
#include "Charger.h"
#include "Bases.h"
#include "Base.h"
#include "Refineries.h"
#include "Refinery.h"
#include "Bulletins.h"
#include "Bulletin.h"
#include "Packet.h"
#include "GoldMines.h"
#include "Miners.h"
#include "Pioneers.h"
#include "Forests.h"
#include "Guardians.h"
#include "Enemies.h"
#include "Guardians.h"
#include "Viewer.h"
#include "Powerplant.h"
#include "Ground.h"
#include "Framework.h"
#include "Keyboard.h"
#include "Coord.h"
#include "Chip.h"
#include "Binary.h"
#include <assert.h>

static const int POWERPLANT_POS_X = 12;
static const int POWERPLANT_POS_Y = 9;

AppPtr App::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< App >( fw->getTask( getTag( ) ) );
}

App::App( ) {
	// リソース読み込み
	BinaryPtr binary = BinaryPtr( new Binary );
	FrameworkPtr fw = Framework::getInstance( );
	fw->loadBinary( "resource2D/map.grd", binary );

	_ground		= GroundPtr    ( new Ground( binary ) );

	_map = MapPtr( new Map( ) );
	_unit_map = UnitMapPtr( new UnitMap( ) );
	_powerplant = PowerplantPtr( new Powerplant( _map, _ground ) );
	_chargers   = ChargersPtr  ( new Chargers  ( ) );
	
	_gold_mines = GoldMinesPtr ( new GoldMines ( _map ) );
	_forests	= ForestsPtr   ( new Forests   ( _map ) );
	_miners		= MinersPtr	   ( new Miners	   ( _unit_map ) );
	_pioneers	= PioneersPtr  ( new Pioneers( _unit_map ) );
	_refineries = RefineriesPtr( new Refineries( _gold_mines, _miners ) );
	_bulletins  = BulletinsPtr ( new Bulletins ( _forests, _pioneers ) );
	_enemies    = EnemiesPtr   ( new Enemies   ( _unit_map, _map, _bulletins, _refineries ) );
	_guardians  = GuardiansPtr ( new Guardians ( _unit_map, _enemies, _map ) );
	_bases      = BasesPtr     ( new Bases     ( _enemies, _guardians ) );
	
	_chargers->initialize( _map, _ground );
	_bases->initialize( _map, _ground );
	_refineries->initialize( _map, _ground );
	_bulletins->initialize( _map, _ground );

	// 発電所は最初から設置されている
	bool result_powerplant_installation = _powerplant->install( Coord( POWERPLANT_POS_X, POWERPLANT_POS_Y ), 0 );
	assert( result_powerplant_installation );
	_line = LinePtr( new Line( _map, _powerplant, _chargers, _bases, _refineries, _bulletins ) );
	_mode = MODE_LINE;
	_bases->install( Coord( 10, 10 ) );
	//_gold = 0;
	_line_guide_flag = false;
}

App::~App( ) {

}

void App::update( ) {
	// サンプル入力
	// マウスでクリックしたところにラインを設定する
	doPlacementOperation( );
	_powerplant->update( );
	_refineries->update( );
	_bulletins->update( );
	_bases->update( );
	_miners->update( );
	_pioneers->update( );
	_enemies->update( );
	_guardians->update( );
	_line->update( );

}
	

void App::doPlacementOperation( ) {
	
	doChangePlacementOperation( );

	switch ( _mode ) {
	case MODE_LINE:
		doLinePlacementOperation( );
		doFacilityMoveOperation( );
		break;
	case MODE_PLACEMENT:
		doFacilityPlacementOperation( );
		break;
	case MODE_DELETE_LINE:
		doLineDeleteOperation( );
		break;
	}
}

void App::doChangePlacementOperation( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );
	
	if ( keyboard->isPushKey( "F1" ) ) {
		_mode = MODE_LINE;
	}
	if ( keyboard->isPushKey( "F2" ) ) {
		_line->cancelGuide( );
		_mode = MODE_PLACEMENT;
		_placement_facility = FACILITY_CHARGER;
	}
	if ( keyboard->isPushKey( "F3" ) ) {
		_line->cancelGuide( );
		_mode = MODE_PLACEMENT;
		_placement_facility = FACILITY_BASE;
	}
	if ( keyboard->isPushKey( "F4" ) ) {
		_line->cancelGuide( );
		_mode = MODE_PLACEMENT;
		_placement_facility = FACILITY_REFINERY;
	}
	if ( keyboard->isPushKey( "F5" ) ) {
		_line->cancelGuide( );
		_mode = MODE_PLACEMENT;
		_placement_facility = FACILITY_BULLETIN;
	}
}

void App::doFacilityMoveOperation( ) {
	ViewerPtr viewer = Viewer::getTask( ); 
	if ( !viewer ) {
		return;
	}
	Coord coord = viewer->getClickCoord( );
	Viewer::CLICK click_left  = viewer->getClickLeft( );

	if ( click_left != Viewer::CLICK_PUSH ) {
		return;
	}
	Map::Chip chip = _map->getChip( coord );
	FacilityConstPtr facility;
	switch( chip.type ) {
	case CHIP_TYPE_CHARGER:
		facility =  _chargers->get( chip.value );
		_mode = MODE_PLACEMENT;
		_placement_facility = FACILITY_CHARGER;
		break;
	case CHIP_TYPE_BASE:
		facility =  _bases->get( chip.value );
		_mode = MODE_PLACEMENT;
		_placement_facility = FACILITY_BASE;
		break;
	case CHIP_TYPE_REFINERY:
		facility =  _refineries->get( chip.value );
		_mode = MODE_PLACEMENT;
		_placement_facility = FACILITY_REFINERY;
		break;
	case CHIP_TYPE_BULLETIN:
		facility =  _bulletins->get( chip.value );
		_mode = MODE_PLACEMENT;
		_placement_facility = FACILITY_BULLETIN;
		break;
	default:
		return;
	}

	Coord left = facility->getLineFixationLeft( );
	left.x++;
	Coord right = facility->getLineFixationRight( );
	right.x--;
	if( left.getIdx( ) == coord.getIdx( ) ||
		right.getIdx( ) == coord.getIdx( ) ) {
		_mode = MODE_LINE;
		return;
	}

	_operating_relocation = true;
	_relocation_idx = chip.value;
	_before_coord = coord;
}

void App::doLineDeleteOperation( ) {

	ViewerPtr viewer = Viewer::getTask( ); 
	if ( !viewer ) {
		return;
	}
	
	Coord coord = viewer->getClickCoord( );
	Viewer::CLICK click_left  = viewer->getClickLeft( );

	if ( click_left == Viewer::CLICK_PUSH ) {
		 _line->deleteAlongGuide( coord );
		_mode = MODE_LINE;
	}
}

void App::doLinePlacementOperation( ) {

	ViewerPtr viewer = Viewer::getTask( ); 
	if ( !viewer ) {
		return;
	}

	Coord coord = viewer->getClickCoord( );
	Viewer::CLICK click_left  = viewer->getClickLeft( );

	if ( click_left == Viewer::CLICK_PUSH ) {
		_click_push_coord = coord;
		_line->startGuide( coord );
	}

	if ( _line_guide_flag ) {
		if ( !_line->setGuideAlongMouse( coord ) ) {
			_line_guide_flag = !_line_guide_flag;
			_line->cancelGuide( );
		}
	}

	if ( click_left == Viewer::CLICK_RELEASE ) {
		if( _line_guide_flag ) {
			_line->cancelGuide( );
		}
		if( _click_push_coord.getIdx( ) != coord.getIdx( ) ){
			return;
		}
		if ( _line->setDeleteGuide( coord ) ) {
			_mode = MODE_DELETE_LINE;
		}

		
		_line_guide_flag = !_line_guide_flag;
	}
	
}

void App::doFacilityPlacementOperation( ) {
	
	ViewerPtr viewer = Viewer::getTask( ); 
	if ( !viewer ) {
		return;
	}

	Viewer::GUIDE guide;
	FacilitiesPtr facilities;
	switch ( _placement_facility ) {
	case FACILITY_CHARGER:
		guide = Viewer::GUIDE_CHARGER;
		facilities = _chargers;
		break;
	case FACILITY_BASE:
		guide = Viewer::GUIDE_BASE;
		facilities = _bases;
		break;
	case FACILITY_REFINERY:
		guide = Viewer::GUIDE_REFINERY;
		facilities = _refineries;
		break;
	case FACILITY_BULLETIN:
		guide = Viewer::GUIDE_BULLETIN;
		facilities = _bulletins;
		break;


	default:
		assert( false );
	};

	Coord coord = viewer->getClickCoord( );
	viewer->setGuidFacility( coord, guide );
	
	Viewer::CLICK click_left  = viewer->getClickLeft( );
	if ( click_left != Viewer::CLICK_PUSH ) {
		return;
	}
	
	if ( !_operating_relocation ) {
		facilities->install( coord );
	} else {
		if ( coord.getIdx( ) != _before_coord.getIdx( ) ) {
			FacilityConstPtr facility = facilities->get( _relocation_idx );

			Coord left_coord = facility->getLineFixationLeft( );
			if ( _line->getChip( left_coord ).form_dir != Line::DIR_NONE ) {
				_line->setDeleteGuide( facility->getLineFixationLeft( ) );
				_line->deleteAlongGuide( facility->getLineFixationLeft( ) );
			}

			Coord right_coord = facility->getLineFixationRight( );
			if ( _line->getChip( right_coord ).form_dir != Line::DIR_NONE ) {
				_line->setDeleteGuide( facility->getLineFixationRight( ) );
				_line->deleteAlongGuide( facility->getLineFixationRight( ) );
			}
			facilities->relocation( coord, _relocation_idx );
		}
	}
	
	_operating_relocation = false;
	_mode = MODE_LINE;
}

MapConstPtr App::getMap( ) const {
	return _map;
}

MapPtr App::getMap( ) {
	return _map;
}

UnitMapConstPtr App::getUnitMap( ) const {
	return _unit_map;
}

UnitMapPtr App::getUnitMap( ) {
	return _unit_map;
}

PowerplantConstPtr App::getPowerplant( ) const {
	return _powerplant;
}

ChargersConstPtr App::getChargers( ) const {
	return _chargers;
}

BasesConstPtr App::getBases( ) const {
	return _bases;
}

RefineriesConstPtr App::getRefineries( ) const {
	return _refineries;
}

BulletinsConstPtr App::getBulletins( ) const {
	return _bulletins;
}

LineConstPtr App::getLine( ) const {
	return _line;
}


GoldMinesPtr App::getGoldMines( ) {
	return _gold_mines;
}

ForestsPtr App::getForests( ) {
	return _forests;
}

MinersConstPtr App::getMiners( ) const {
	return _miners;
}

MinersPtr App::getMiners( ) {
	return _miners;
}

PioneersConstPtr App::getPioneers( ) const {
	return _pioneers;
}

EnemiesPtr App::getEnemies( ) const {
	return _enemies;
}

GuardiansPtr App::getGuardians( ) const {
	return _guardians;
}

GroundPtr App::getGround( ) const {
	return _ground;
}

bool App::isModeDeleteLine( ) const {
	if ( _mode == MODE_DELETE_LINE ) {
		return true;
	}
	return false;
}