
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
#include "Coord.h"
#include "Chip.h"
#include <assert.h>

const int POWERPLANT_LEVEL = 10; //仮

Line::Line( MapPtr map, PowerplantPtr powerplant, ChargersPtr chargers, BasesPtr bases, RefineriesPtr refineries, BulletinsPtr bulletins ) :
_map( map ),
_powerplant( powerplant ),
_chargers( chargers ),
_bases( bases ),
_refineries( refineries ),
_bulletins( bulletins ) {
	for ( int i = 0; i < COORD_HEIGHT * COORD_WIDTH; i++ ) {
		_data.array[ i ].form_dir = DIR_NONE;
		_data.array[ i ].circuit_dir = DIR_NONE;
		_data.array[ i ].is_check = false;
		_data.array[ i ].guide = false;
	}
	_guide_mode = false;
	_delete_coord_first_conecter  = Coord( -1, -1 );
	_delete_coord_second_conecter = Coord( -1, -1 );
}

Line::~Line( ) {

}

void Line::update( ) {
}

void Line::makeCircuit( ) {
	// 循環経路削除
	for ( int i = 0; i < COORD_WIDTH * COORD_HEIGHT; i++ ) {
		_data.array[ i ].circuit_dir = DIR_NONE;
		_data.array[ i ].is_check = false;
	}
	
	// パワープラントにつながっているか？
	Coord start_coord = _powerplant->getLineOutCoord( );
	Coord end_coord = _powerplant->getLineInCoord( );
	if ( start_coord.getIdx( ) < 0 || end_coord.getIdx( ) < 0 ) {
		return;
	}

	// 循環経路作成
	makeCircuitNext( _powerplant->getStartCoord( ), start_coord );
}

bool Line::isGuiding( ) const {
	return _guide_mode;
}

const Line::Data& Line::getData( ) const {
	return _data;
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
	_guide_store_from_dir = DIR_NONE;
	_guide_store_circuit_dir = DIR_NONE;
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
	if ( _data.array[ coord.getIdx( ) ].guide ) {
		cancelGuide( );
		return;
	}
	
	unsigned char now_dir = getNowDir( coord, _old_coord );

	// 一つ前を正式なラインにする
	if ( _data.array[ _old_coord.getIdx( ) ].guide ) {
		unsigned char old_dir = _data.array[ _old_coord.getIdx( ) ].form_dir;
		_data.array[ _old_coord.getIdx( ) ].form_dir = old_dir | reverseDir( now_dir );
	}
	 
	// 始点
	if ( _guide_start_coord.getIdx( ) == _old_coord.getIdx( ) ) {
		_guide_store_from_dir = _data.array[ _old_coord.getIdx( ) ].form_dir;
		_guide_store_circuit_dir = _data.array[ _old_coord.getIdx( ) ].circuit_dir;
		_line_start_coord = coord;
		//始点がラインのとき、T字のラインにする
		if ( _guide_store_from_dir != DIR_NONE ) {
			unsigned dir = reverseDir( now_dir ) | _guide_store_from_dir;
			_data.array[ _old_coord.getIdx( ) ].form_dir = dir;
			_data.array[ _old_coord.getIdx( ) ].guide = true;
		}
	}

	// 終端である
	if ( _map->getChip( coord ).type != CHIP_TYPE_NONE ) {
		endGuide( coord );
		return;
	}
	
	// 仮で設定
	_data.array[ coord.getIdx( ) ].form_dir = now_dir;
	_data.array[ coord.getIdx( ) ].guide = true;

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
		unsigned char before_dir = _data.array[ idx ].form_dir;
		_data.array[ idx ].form_dir = before_dir | now_dir;
	}
	
	// 正式なラインに変更
	for ( int i = 0; i < COORD_HEIGHT * COORD_WIDTH; i++ ) {
		if ( !_data.array[ i ].guide ) {
			continue;
		}		
		_data.array[ i ].guide = false;
		Coord coord( i % COORD_WIDTH, i / COORD_WIDTH );
		Map::Chip chip;
		chip.type = CHIP_TYPE_LINE;
		_map->setChip( coord, chip );
	}


	makeCircuit( );
	_guide_mode = false;
	_guide_store_from_dir = DIR_NONE;
	_guide_store_circuit_dir = DIR_NONE;
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
		if ( _data.array[ i ].guide ) { 
			_data.array[ i ].form_dir = DIR_NONE;
			_data.array[ i ].circuit_dir = DIR_NONE;
			_data.array[ i ].guide = false;
		}
	}
	if ( _guide_store_from_dir != DIR_NONE ) {
		_data.array[ _guide_start_coord.getIdx( ) ].form_dir = _guide_store_from_dir;
		_data.array[ _guide_start_coord.getIdx( ) ].circuit_dir = _guide_store_circuit_dir;
		_data.array[ _guide_start_coord.getIdx( ) ].guide = false;
		_guide_store_from_dir = DIR_NONE;
		_guide_store_circuit_dir = DIR_NONE;
		_guide_start_coord = Coord( -1, -1 );
	}
}

bool Line::makeCircuitNext( const Coord& coord, const Coord& old_coord ) {
	
	// 探索先のチップがラインではない
	if ( coord.getIdx( ) < 0 ) {
		return false;
	}
	
	// ※事前にこのCoordが存在することは調べてある
	Coord end_coord = _powerplant->getLineInCoord( );

	// 最終到達点に達した
	if ( coord.getIdx( ) == end_coord.getIdx( ) ) {
		// PowerPlantのゴールに到達した
		return true;
	}
	if ( _data.array[ coord.getIdx( ) ].circuit_dir != DIR_NONE ) {
		return true;
	}
	// Facilityチップか？
	if ( ( _map->getChip( coord ).type & CHIP_TYPE_FACILITY ) != 0 ) {
		return setConnectFacility( coord );
	}
	
	//新しいチップであるか
	if ( !_data.array[ coord.getIdx( ) ].is_check ) {
		// 新しいチップでのチェック
		return setConnectNew( coord, old_coord );
	}
	
	return false;
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
	return makeCircuitNext( exit_coord, coord );
}


bool Line::setConnectNew( const Coord& coord, const Coord& old_coord ) {

	unsigned char now_type = _data.array[ coord.getIdx( ) ].form_dir;
	unsigned char now_dir = getNowDir( coord, old_coord );
	unsigned char next_dir = now_type & ~now_dir;
	_data.array[ coord.getIdx( ) ].is_check = true;
	setConnectNext( coord, next_dir );
	return _data.array[ coord.getIdx( ) ].circuit_dir != DIR_NONE;
}

void Line::setConnectNext( const Coord& coord, unsigned char next_dir ) {
	if ( next_dir & DIR_U___ ) {
		Coord up_coord    = Coord( coord.x, coord.y - 1 );
		if ( makeCircuitNext( up_coord , coord ) ) {
			_data.array[ coord.getIdx( ) ].circuit_dir = _data.array[ coord.getIdx( ) ].circuit_dir | DIR_U___;
		}
	}
	if ( next_dir & DIR__D__ ) {
		Coord down_coord  = Coord( coord.x, coord.y + 1 );
		if ( makeCircuitNext( down_coord, coord ) ) {
			_data.array[ coord.getIdx( ) ].circuit_dir = _data.array[ coord.getIdx( ) ].circuit_dir | DIR__D__;
		}
	}
	if ( next_dir & DIR___L_ ) {
		Coord left_coord  = Coord( coord.x - 1, coord.y );
		if ( makeCircuitNext( left_coord, coord ) ) {
			_data.array[ coord.getIdx( ) ].circuit_dir = _data.array[ coord.getIdx( ) ].circuit_dir | DIR___L_;
		}
	}
	if ( next_dir & DIR____R ) {
		Coord right_coord = Coord( coord.x + 1, coord.y );
		if ( makeCircuitNext( right_coord, coord ) ) {
			_data.array[ coord.getIdx( ) ].circuit_dir = _data.array[ coord.getIdx( ) ].circuit_dir | DIR____R;
		}
	}
	_data.array[ coord.getIdx( ) ].is_check = false;
}

bool Line::setDeleteGuide( const Coord& coord ) {
	if ( _map->getChip( coord ).type != CHIP_TYPE_LINE ) {
		return false;
	}

	_delete_coord_first_conecter  = Coord( -1, -1 );
	_delete_coord_second_conecter = Coord( -1, -1 );

	unsigned char state = _data.array[ coord.getIdx( ) ].form_dir;

	if ( state & DIR_U___ ) {
		Coord up_coord    = Coord( coord.x, coord.y - 1 );
		checkDelete( coord, up_coord );
	}
	if ( state & DIR__D__ ) {
		Coord down_coord  = Coord( coord.x, coord.y + 1 );
		checkDelete( coord, down_coord );
	}
	if ( state & DIR___L_ ) {
		Coord left_coord  = Coord( coord.x - 1, coord.y );
		checkDelete( coord, left_coord );
	}
	if ( state & DIR____R ) {
		Coord right_coord = Coord( coord.x + 1, coord.y );
		checkDelete( coord, right_coord );
	}
	_guide_mode = true;
	return true;
}

// 戻り値 true : 終端 false : まだ続く
bool Line::checkDelete( const Coord& coord, const Coord& old_coord ) {
	// 対象のチップがLineまたはFacilityである場合
	CHIP_TYPE type = _map->getChip( coord ).type;
	unsigned char form_dir = _data.array[ coord.getIdx( ) ].form_dir;
	if ( type == CHIP_TYPE_CHARGER    ||
		 type == CHIP_TYPE_BASE       ||
		 type == CHIP_TYPE_REFINERY   ||
		 type == CHIP_TYPE_BULLETIN   ||
		 type == CHIP_TYPE_POWERPLANT ||
		 form_dir == DIR_U_LR ||
		 form_dir == DIR__DLR || 
		 form_dir == DIR_UD_R || 
		 form_dir == DIR_UDL_ ||
		 form_dir == DIR_UDLR ) {
		if ( _delete_coord_first_conecter.getIdx( ) > 0  ) {
			_delete_coord_second_conecter = coord;
		} else {
			_delete_coord_first_conecter = coord;
		}
		return true;
	}
	
	// 次のチップへ
	return setDeleteNew( coord, old_coord );
}

bool Line::setDeleteNew( const Coord& coord, const Coord& old_coord ) {

	unsigned char now_type = _data.array[ coord.getIdx( ) ].form_dir;
	unsigned char now_dir = getNowDir( coord, old_coord );
	unsigned char next_dir = now_type & ~now_dir;
	_data.array[ coord.getIdx( ) ].is_check = true;
	setDeleteNext( coord, next_dir );
	return _data.array[ coord.getIdx( ) ].guide;
}

void Line::setDeleteNext( const Coord& coord, unsigned char next_dir) {
	
	if ( checkDeleteDir( coord, next_dir ) ) {
		_data.array[ coord.getIdx( ) ].guide = true;
	}
}

bool Line::checkDeleteDir ( const Coord& coord, unsigned char next_dir ) {
	bool check = false;
	if ( next_dir & DIR_U___ ) {
		Coord up_coord    = Coord( coord.x, coord.y - 1 );
		if ( checkDelete( up_coord , coord ) ) {
			check = true;
		}
	}
	if ( next_dir & DIR__D__ ) {
		Coord down_coord  = Coord( coord.x, coord.y + 1 );
		if ( checkDelete( down_coord, coord ) ) {
			check = true;
		}
	}
	if ( next_dir & DIR___L_ ) {
		Coord left_coord  = Coord( coord.x - 1, coord.y );
		if ( checkDelete( left_coord, coord ) ) {
			check = true;
		}
	}
	if ( next_dir & DIR____R ) {
		Coord right_coord = Coord( coord.x + 1, coord.y );
		if ( checkDelete( right_coord, coord ) ) {
			check = true;
		}
	}
	_data.array[ coord.getIdx( ) ].is_check = false;

	return check;
}

void Line::deleteAlongGuide( const Coord& coord ) {
	_guide_mode = false;
	bool is_decide_delete = _data.array[ coord.getIdx( ) ].guide;

	for ( int i = 0; i < COORD_HEIGHT * COORD_WIDTH; i++ ) {
		if ( !_data.array[ i ].guide ) {
			continue;
		}
		if ( is_decide_delete ) {
			_data.array[ i ].form_dir = DIR_NONE;
			_data.array[ i ].circuit_dir = DIR_NONE;
			_data.array[ i ].is_check = false;

			Map::Chip chip;
			chip.type = CHIP_TYPE_NONE;
			chip.value = 0;			
			_map->setChip( i, chip );
		} 
		_data.array[ i ].guide = false;
	}

	bool destroy_first_flag = destroyLineDir( _map->getChip( _delete_coord_first_conecter ).type, _delete_coord_first_conecter );
	bool destroy_second_flag = destroyLineDir( _map->getChip( _delete_coord_second_conecter ).type, _delete_coord_second_conecter );

	makeCircuit( );
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
		_data.array[ coord.getIdx( ) ].form_dir = _data.array[ coord.getIdx( ) ].form_dir & ~DIR_U___;
		ret = true;
	}
	if ( _map->getChip( down_coord ).type == CHIP_TYPE_NONE ) {
		_data.array[ coord.getIdx( ) ].form_dir = _data.array[ coord.getIdx( ) ].form_dir & ~DIR__D__;
		ret = true;
	}
	if ( _map->getChip( left_coord ).type == CHIP_TYPE_NONE ) {
		_data.array[ coord.getIdx( ) ].form_dir = _data.array[ coord.getIdx( ) ].form_dir & ~DIR___L_;
		ret = true;
	}
	if ( _map->getChip( right_coord ).type == CHIP_TYPE_NONE ) {
		_data.array[ coord.getIdx( ) ].form_dir = _data.array[ coord.getIdx( ) ].form_dir & ~DIR____R;
		ret = true;
	}
	return ret;

}