
#include "Line.h"
#include "Map.h"
#include "Powerplant.h"
#include "Bases.h"
#include "Base.h"
#include "Refineries.h"
#include "Refinery.h"
#include "Bulletins.h"
#include "Bulletin.h"
#include "Chargers.h"
#include "Charger.h"
#include "Facility.h"
#include "App.h"
#include "Coord.h"
#include "Chip.h"
#include <assert.h>

Line::Line( MapPtr map, PowerplantPtr powerplant, ChargersPtr chargers, BasesPtr bases, RefineriesPtr refineries, BulletinsPtr bulletins ) :
_map( map ),
_powerplant( powerplant ),
_chargers( chargers ),
_bases( bases ),
_refineries( refineries ),
_bulletins( bulletins ) {
	for ( int i = 0; i < COORD_HEIGHT * COORD_WIDTH; i++ ) {
		_data.array[ i ].type = DIR_NONE;
		_data.array[ i ].state = STATE_NONE;
		_data.array[ i ].is_check = false;
	}
	_guide_mode = false;
	_delete_coord_first_conecter  = Coord( -1, -1 );
	_delete_coord_second_conecter = Coord( -1, -1 );
}

Line::~Line( ) {

}

void Line::reflesh( ) {
	// 循環経路削除
	for ( int i = 0; i < COORD_WIDTH * COORD_HEIGHT; i++ ) {
		if ( _data.array[ i ].state == STATE_CIRCUIT || _data.array[ i ].state == STATE_DELETE ) { 
			_data.array[ i ].state = STATE_NORMAL;
		}
		_data.array[ i ].is_check = false;
	}
	
	
	// パワープラントにつながっているか？
	Coord start_coord = getFacilityConnectCoord( _powerplant->getLineOutCoord( ) );
	Coord end_coord = getFacilityConnectCoord( _powerplant->getLineInCoord( ) );
	if ( start_coord.getIdx( ) < 0 || end_coord.getIdx( ) < 0 ) {
		return;
	}

	// 循環経路作成
	makeCircuit( _powerplant->getLineOutCoord( ), start_coord );
}

bool Line::isGuiding( ) const {
	return _guide_mode;
}

const Line::Data& Line::getData( ) const {
	return _data;
}

Coord Line::getFacilityConnectCoord( const Coord& coord ) {
	if ( coord.getIdx( ) < 0 ) {
		return coord;
	}
	if ( _map->getChip( Coord( coord.x - 1, coord.y ) ).type == CHIP_TYPE_CHARGER	 ||
		 _map->getChip( Coord( coord.x - 1, coord.y ) ).type == CHIP_TYPE_BASE		 ||
		 _map->getChip( Coord( coord.x - 1, coord.y ) ).type == CHIP_TYPE_REFINERY	 ||
		 _map->getChip( Coord( coord.x - 1, coord.y ) ).type == CHIP_TYPE_BULLETIN	 ||
		 _map->getChip( Coord( coord.x - 1, coord.y ) ).type == CHIP_TYPE_POWERPLANT ) {
		return Coord( coord.x - 1, coord.y );				 
	}														 
	if ( _map->getChip( Coord( coord.x + 1, coord.y ) ).type == CHIP_TYPE_CHARGER	 ||
		 _map->getChip( Coord( coord.x + 1, coord.y ) ).type == CHIP_TYPE_BASE		 ||
		 _map->getChip( Coord( coord.x + 1, coord.y ) ).type == CHIP_TYPE_REFINERY	 ||
		 _map->getChip( Coord( coord.x + 1, coord.y ) ).type == CHIP_TYPE_BULLETIN	 ||
		 _map->getChip( Coord( coord.x + 1, coord.y ) ).type == CHIP_TYPE_POWERPLANT ) {
		return Coord( coord.x + 1, coord.y );
	}
	return coord;
}

void Line::startGuide( const Coord& coord ) {
	Map::Chip chip = _map->getChip( coord );
	if ( chip.type == CHIP_TYPE_NONE  ) {
		return;
	}
	FacilityConstPtr facility = getChipType( chip.type, chip.value );

	if ( facility != NULL ) {
		if ( facility->getLineFixationLeft( ).getIdx( )  != coord.getIdx( ) &&
			 facility->getLineFixationRight( ).getIdx( ) != coord.getIdx( ) ) {
			return;
		}
	}
	_guide_mode = true;
	_old_coord = coord;
	_guide_store_dir = DIR_NONE;
	_guide_start_coord = coord;
}

void Line::setGuide( const Coord& coord ) {
	// ガイドしない
	if ( !_guide_mode ) {
		return;
	}
	if ( _old_coord.getIdx( ) == coord.getIdx( ) ) {
		return;
	}

	// ガイド中止
	if ( ( abs( _old_coord.x - coord.x ) > 1 || _old_coord.y != coord.y ) &&
		 ( abs( _old_coord.y - coord.y ) > 1 || _old_coord.x != coord.x ) ) {
		cancelGuide( );
		return;
	}
	if ( _data.array[ coord.getIdx( ) ].state == STATE_GUIDE ) {
		cancelGuide( );
		return;
	}
	
	unsigned char now_dir = getNowDir( coord, _old_coord );

	// 一つ前を正式なラインにする
	if ( _data.array[ _old_coord.getIdx( ) ].state == STATE_GUIDE ) {
		unsigned char old_dir = _data.array[ _old_coord.getIdx( ) ].type;
		_data.array[ _old_coord.getIdx( ) ].type = old_dir | reverseDir( now_dir );
	}
	 
	// 始点
	if ( _guide_start_coord.getIdx( ) == _old_coord.getIdx( ) ) {
		_guide_store_dir = _data.array[ _old_coord.getIdx( ) ].type;
		_guide_store_state = _data.array[ _old_coord.getIdx( ) ].state;
		_line_start_coord = coord;
		//始点がラインのとき、T字のラインにする
		if ( _guide_store_dir != DIR_NONE ) {
			unsigned dir = reverseDir( now_dir ) | _guide_store_dir;
			_data.array[ _old_coord.getIdx( ) ].type = dir;
			_data.array[ _old_coord.getIdx( ) ].state = STATE_GUIDE;
		}
	}

	// 終端である
	if ( _map->getChip( coord ).type != CHIP_TYPE_NONE ) {
		endGuide( coord );
		return;
	}
	
	// 仮で設定
	_data.array[ coord.getIdx( ) ].type = now_dir;
	_data.array[ coord.getIdx( ) ].state = STATE_GUIDE;

	_old_coord = coord;
}

void Line::endGuide( const Coord& coord ) {
	if ( !_guide_mode ) {
		return;
	}

	Map::Chip start_chip = _map->getChip( _guide_start_coord );
	Map::Chip end_chip = _map->getChip( coord );
	
	FacilityConstPtr facility = getChipType( end_chip.type, end_chip.value );

	if ( facility != NULL ) {
		if ( facility->getLineFixationLeft( ).getIdx( )  != coord.getIdx( ) &&
			 facility->getLineFixationRight( ).getIdx( ) != coord.getIdx( ) ) {
			return;
		}
	}
	// 終点がラインだったら、連結処理をする
	if ( _map->getChip( coord ).type == CHIP_TYPE_LINE ) {
		int idx = coord.getIdx( );
		unsigned char now_dir = getNowDir( coord, _old_coord );
		unsigned char before_dir = _data.array[ idx ].type;
		_data.array[ idx ].type = before_dir | now_dir;
	}
	
	// 正式なラインに変更
	for ( int i = 0; i < COORD_HEIGHT * COORD_WIDTH; i++ ) {
		if ( _data.array[ i ].state != STATE_GUIDE ) {
			continue;
		}
		_data.array[ i ].state = STATE_NORMAL;
		Coord coord( i % COORD_WIDTH, i / COORD_WIDTH );
		Map::Chip chip;
		chip.type = CHIP_TYPE_LINE;
		_map->setChip( coord, chip );
	}


	reflesh( );
	_guide_store_dir = DIR_NONE;
	_guide_mode = false;
}

FacilityConstPtr Line::getChipType( CHIP_TYPE chip_type, unsigned char value  ) {
	FacilityConstPtr facility;
	switch( chip_type ) {
	case CHIP_TYPE_POWERPLANT:
		facility = _powerplant;
		break;
	case CHIP_TYPE_CHARGER:
		facility = _chargers->get( value );
		break;
	case CHIP_TYPE_BASE:
		facility = _bases->get( value );
		break;
	case CHIP_TYPE_REFINERY:
		facility = _refineries->get( value );
		break;
	case CHIP_TYPE_BULLETIN:
		facility = _bulletins->get( value );
		break;
	case CHIP_TYPE_LINE:
		facility = NULL;
		break;
	default:
		assert( false );
	}
	return facility;
}
 


void Line::cancelGuide( ) {
	initGuideArray( );
	_guide_mode = false;
}

unsigned char Line::getNowDir ( const Coord& coord, const Coord& old_coord ) {
	unsigned char ret_dir = DIR_NONE;
	if ( coord.x > old_coord.x ) {
		ret_dir = DIR___L_;
	}
	if ( coord.x < old_coord.x ) {
		ret_dir = DIR____R;
	}	
	if ( coord.y > old_coord.y ) {
		ret_dir = DIR_U___;
	}	
	if ( coord.y < old_coord.y ) {
		ret_dir = DIR__D__;
	}
	return ret_dir;
}

unsigned char Line::reverseDir( unsigned char dir ) const {
	unsigned char ret_dir = DIR_NONE;
	switch ( dir ) {
	case DIR____R:
		ret_dir = DIR___L_;
		break;
	case DIR___L_:
		ret_dir = DIR____R;
		break;
	case DIR_U___:
		ret_dir = DIR__D__;
		break;
	case DIR__D__:
		ret_dir = DIR_U___;
		break;
	}
	return ret_dir;
}

void Line::initGuideArray( ) { 
	for ( int i = 0; i < COORD_HEIGHT * COORD_WIDTH; i++ ) {
		if ( _data.array[ i ].state == STATE_GUIDE ) { 
			_data.array[ i ].type = DIR_NONE;
			_data.array[ i ].state = STATE_NONE;
		}
	}
	if ( _guide_store_dir != DIR_NONE ) {
		_data.array[ _guide_start_coord.getIdx( ) ].type = _guide_store_dir;
		_data.array[ _guide_start_coord.getIdx( ) ].state = _guide_store_state;
		_guide_store_dir = DIR_NONE;
		_guide_start_coord = Coord( -1, -1 );
	}
}

bool Line::makeCircuit( const Coord& coord, const Coord& old_coord ) {
	
	// 探索先のチップがラインではない
	if ( coord.getIdx( ) < 0 ) {
		return false;
	}
	
	// ※事前にこのCoordが存在することは調べてある
	Coord end_coord = getFacilityConnectCoord( _powerplant->getLineInCoord( ) );

	// 最終到達点に達した
	if ( coord.getIdx( ) == end_coord.getIdx( ) ) {
		// PowerPlantのゴールに到達した
		return true;
	}
	if ( _data.array[ coord.getIdx( ) ].state == STATE_CIRCUIT ) {
		return true;
	}
	// Facilityチップか？
	if ( ( _map->getChip( coord ).type & CHIP_TYPE_FACILITY ) != 0 ) {
		return setConnectFacility( coord );
	}
	
	//新しいチップであるか
	if ( !_data.array[ coord.getIdx( ) ].is_check ) {
		// 新しいチップでのチェック
		return setConnectNew( coord, old_coord, STATE_CIRCUIT );
	}
	
	return true;
}

bool Line::checkDelete( const Coord& coord, const Coord& old_coord ) {
	CHIP_TYPE type = _map->getChip( coord ).type;
	if ( type == CHIP_TYPE_CHARGER || type == CHIP_TYPE_BASE || type == CHIP_TYPE_REFINERY ||
		 type == CHIP_TYPE_BULLETIN || type == CHIP_TYPE_POWERPLANT ) {
		if ( _delete_coord_first_conecter.getIdx( ) > 0  ) {
			_delete_coord_second_conecter = old_coord;
		} else {
			_delete_coord_first_conecter = old_coord;
		}

		return true;
	}
	if ( _data.array[ coord.getIdx( ) ].type == DIR_U_LR ||
		 _data.array[ coord.getIdx( ) ].type == DIR__DLR || 
		 _data.array[ coord.getIdx( ) ].type == DIR_UD_R || 
		 _data.array[ coord.getIdx( ) ].type == DIR_UDL_ ||
		 _data.array[ coord.getIdx( ) ].type == DIR_UDLR ) {
		if ( _delete_coord_first_conecter.getIdx( ) > 0  ) {
			_delete_coord_second_conecter = coord;
		} else {
			_delete_coord_first_conecter = coord;
		}
		return true;
	}
	
	//新しいチップであるか
	if ( !_data.array[ coord.getIdx( ) ].is_check ) {
		// 新しいチップでのチェック
		return setConnectNew( coord, old_coord, STATE_DELETE );
	}
	return true;
}

bool Line::setConnectFacility( const Coord& coord ) {
	Map::Chip chip = _map->getChip( coord );
	FacilityConstPtr facility;
	switch ( chip.type ) {
	case CHIP_TYPE_POWERPLANT:
		facility = _powerplant;
		break;
	case CHIP_TYPE_CHARGER:
		facility = _chargers->get( chip.value );
		break;
	case CHIP_TYPE_BASE:
		facility = _bases->get( chip.value );
		break;
	case CHIP_TYPE_REFINERY:
		facility = _refineries->get( chip.value );
		break;
	case CHIP_TYPE_BULLETIN:
		facility = _bulletins->get( chip.value );
		break;
	default:
		// ここに来ることはありえない
		assert( false );
	}
	
	Coord exit_coord = facility->getExitCoord( coord );
	if ( exit_coord.getIdx( ) < 0 ) {
		return false;
	}
	return makeCircuit( exit_coord, coord );
}


bool Line::setConnectNew( const Coord& coord, const Coord& old_coord, Line::STATE state ) {

	unsigned char now_type = _data.array[ coord.getIdx( ) ].type;
	unsigned char now_dir = getNowDir( coord, old_coord );
	unsigned char next_dir = now_type & ~now_dir;
	_data.array[ coord.getIdx( ) ].is_check = true;
	setConnectNext( coord, next_dir, state );
	if( _data.array[ coord.getIdx( ) ].state == state ) {
		return true;
	}
	return false;
}

void Line::setConnectNext( const Coord& coord, unsigned char next_dir, Line::STATE state ) {
	
	bool check = false;
	switch( state ) {
	case STATE_CIRCUIT:
		check = checkConnectDir( coord, next_dir );
		break;
	case STATE_DELETE:
		check = checkDeleteDir( coord, next_dir );
		break;
	default:
		break;
	}
	if ( check ) {
		_data.array[ coord.getIdx( ) ].state = state;
	}
}

bool Line::checkConnectDir ( const Coord& coord, unsigned char next_dir ) {
	bool check = false;
	Coord up_coord    = Coord( coord.x, coord.y - 1 );
	Coord down_coord  = Coord( coord.x, coord.y + 1 );
	Coord left_coord  = Coord( coord.x - 1, coord.y );
	Coord right_coord = Coord( coord.x + 1, coord.y );
	if ( next_dir & DIR_U___ ) {
		if ( makeCircuit( up_coord , coord ) ) {
			check = true;
		}
	}
	if ( next_dir & DIR__D__ ) {
		if ( makeCircuit( down_coord, coord ) ) {
			check = true;
		}
	}
	if ( next_dir & DIR___L_ ) {
		if ( makeCircuit( left_coord, coord ) ) {
			check = true;
		}
	}
	if ( next_dir & DIR____R ) {
		if ( makeCircuit( right_coord, coord ) ) {
			check = true;
		}
	}
	_data.array[ coord.getIdx( ) ].is_check = false;

	return check;
}

bool Line::checkDeleteDir ( const Coord& coord, unsigned char next_dir ) {
	bool check = false;
	Coord up_coord    = Coord( coord.x, coord.y - 1 );
	Coord down_coord  = Coord( coord.x, coord.y + 1 );
	Coord left_coord  = Coord( coord.x - 1, coord.y );
	Coord right_coord = Coord( coord.x + 1, coord.y );
	if ( next_dir & DIR_U___ ) {
		if ( checkDelete( up_coord , coord ) ) {
			check = true;
		}
	}
	if ( next_dir & DIR__D__ ) {
		if ( checkDelete( down_coord, coord ) ) {
			check = true;
		}
	}
	if ( next_dir & DIR___L_ ) {
		if ( checkDelete( left_coord, coord ) ) {
			check = true;
		}
	}
	if ( next_dir & DIR____R ) {
		if ( checkDelete( right_coord, coord ) ) {
			check = true;
		}
	}
	_data.array[ coord.getIdx( ) ].is_check = false;

	return check;
}


void Line::deleteLine( const Coord& coord ) {
	STATE click_state = _data.array[ coord.getIdx( ) ].state;
	if ( _is_delete ) {
		if( click_state == STATE_DELETE ){
			destroyLine( );
			_is_delete = false;
			_delete_coord_first_conecter  = Coord( -1, -1 );
			_delete_coord_second_conecter = Coord( -1, -1 );
			return;
		} else {
			reflesh( );
		}
		_delete_coord_first_conecter  = Coord( -1, -1 );
		_delete_coord_second_conecter = Coord( -1, -1 );
	}
	_is_delete = true;
	Coord up_coord    = Coord( coord.x, coord.y - 1 );
	Coord down_coord  = Coord( coord.x, coord.y + 1 );
	Coord left_coord  = Coord( coord.x - 1, coord.y );
	Coord right_coord = Coord( coord.x + 1, coord.y );
	unsigned char state = _data.array[ coord.getIdx( ) ].type;

	if ( state & DIR_U___ ) {
		checkDelete( coord, up_coord );
	}
	if ( state & DIR__D__ ) {
		checkDelete( coord, down_coord );
	}
	if ( state & DIR___L_ ) {
		checkDelete( coord, left_coord );
	}
	if ( state & DIR____R ) {
		checkDelete( coord, right_coord );
	}
	
}

void Line::destroyLine( ) {
	for ( int i = 0; i < COORD_HEIGHT * COORD_WIDTH; i++ ) {
		if ( _data.array[ i ].state == STATE_DELETE ) { 
			_data.array[ i ].type = DIR_NONE;
			_data.array[ i ].state = STATE_NONE;
			_data.array[ i ].is_check = false;
			Map::Chip chip;
			chip.type = CHIP_TYPE_NONE;
			chip.value = 0;			
			Coord coord( i % COORD_WIDTH, i / COORD_WIDTH );
			_map->setChip( coord, chip );
		}
	}
	
	Coord first_coord = getFacilityConnectCoord( _delete_coord_first_conecter );
	Coord second_coord = getFacilityConnectCoord( _delete_coord_second_conecter );
	
	Map::Chip first_chip = _map->getChip( first_coord );
	Map::Chip second_chip = _map->getChip( second_coord );

	bool destroy_first_flag = destroyLineDir( _map->getChip( _delete_coord_first_conecter ).type, _delete_coord_first_conecter );
	bool destroy_second_flag = destroyLineDir( _map->getChip( _delete_coord_second_conecter ).type, _delete_coord_second_conecter );

	reflesh( );
}

bool Line::destroyLineDir( CHIP_TYPE type, const Coord& coord ) {
	if ( type != CHIP_TYPE_LINE ) {
		return false;
	}

	Coord up_coord    = Coord( coord.x, coord.y - 1 );
	Coord down_coord  = Coord( coord.x, coord.y + 1 );
	Coord left_coord  = Coord( coord.x - 1, coord.y );
	Coord right_coord = Coord( coord.x + 1, coord.y );
	bool ret = false;
	if ( _map->getChip( up_coord ).type == CHIP_TYPE_NONE ) {
		_data.array[ coord.getIdx( ) ].type = _data.array[ coord.getIdx( ) ].type & ~DIR_U___;
		ret = true;
	}
	if ( _map->getChip( down_coord ).type == CHIP_TYPE_NONE ) {
		_data.array[ coord.getIdx( ) ].type = _data.array[ coord.getIdx( ) ].type & ~DIR__D__;
		ret = true;
	}
	if ( _map->getChip( left_coord ).type == CHIP_TYPE_NONE ) {
		_data.array[ coord.getIdx( ) ].type = _data.array[ coord.getIdx( ) ].type & ~DIR___L_;
		ret = true;
	}
	if ( _map->getChip( right_coord ).type == CHIP_TYPE_NONE ) {
		_data.array[ coord.getIdx( ) ].type = _data.array[ coord.getIdx( ) ].type & ~DIR____R;
		ret = true;
	}
	return ret;

}