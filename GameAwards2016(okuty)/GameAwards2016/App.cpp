#include "App.h"
#include "Powerplant.h"
#include "Map.h"
#include "Line.h"
#include "Chargers.h"
#include "Charger.h"
#include "Bases.h"
#include "Base.h"
#include "Refineries.h"
#include "Refinery.h"
#include "Bulletins.h"
#include "Bulletin.h"
#include "Viewer.h"
#include "Powerplant.h"
#include "Framework.h"
#include "Keyboard.h"
#include "Coord.h"
#include "Chip.h"
#include <assert.h>

static const int POWERPLANT_POS_X = 10;
static const int POWERPLANT_POS_Y = 3;

AppPtr App::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< App >( fw->getTask( getTag( ) ) );
}

App::App( ) {
	// リソース読み込み

	_map = MapPtr( new Map( ) );
	_powerplant = PowerplantPtr( new Powerplant( _map ) );
	_chargers   = ChargersPtr  ( new Chargers  ( ) );
	_bases      = BasesPtr     ( new Bases     ( ) );
	_refineries = RefineriesPtr( new Refineries( ) );
	_bulletins  = BulletinsPtr ( new Bulletins ( ) );

	_chargers->initialize( _map );
	_bases->initialize( _map );
	_refineries->initialize( _map );
	_bulletins->initialize( _map );

	// 発電所は最初から設置されている
	bool result_powerplant_installation = _powerplant->install( Coord( POWERPLANT_POS_X, POWERPLANT_POS_Y ), 0 );
	assert( result_powerplant_installation );

	_line = LinePtr( new Line( _map, _powerplant, _chargers, _bases, _refineries, _bulletins ) );
	_mode = MODE_LINE;
}

App::~App( ) {

}

void App::update( ) {
	// サンプル入力
	// マウスでクリックしたところにラインを設定する
	doPlacementOperation( );
	_powerplant->update( );
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

	if( facility->getLineFixationLeft( ).getIdx( ) == coord.getIdx( ) ||
		facility->getLineFixationRight( ).getIdx( ) == coord.getIdx( ) ) {
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

	if ( click_left == Viewer::CLICK_HOLD ) {
		_line->setGuide( coord );
	}

	if ( click_left == Viewer::CLICK_RELEASE ) {
		_line->cancelGuide( );
		if( _click_push_coord.getIdx( ) != coord.getIdx( ) ){
			return;
		}
		if ( _line->setDeleteGuide( coord ) ) {
			_mode = MODE_DELETE_LINE;
		}
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
			if ( facility->getLineFixationLeft( ).getIdx( ) >= 0 ) {
				_line->setDeleteGuide( facility->getExitCoord( facility->getLineFixationLeft( ) ) );
				_line->deleteAlongGuide( facility->getExitCoord( facility->getLineFixationLeft( ) ) );
			}
			if ( facility->getLineFixationRight( ).getIdx( ) >= 0 ) {
				_line->setDeleteGuide( facility->getExitCoord( facility->getLineFixationRight( ) ) );
				_line->deleteAlongGuide( facility->getExitCoord( facility->getLineFixationRight( ) ) );
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

bool App::isModeDeleteLine( ) const {
	if ( _mode == MODE_DELETE_LINE ) {
		return true;
	}
	return false;
}