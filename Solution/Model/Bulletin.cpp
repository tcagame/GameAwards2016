#include "Bulletin.h"
#include "Chip.h"
#include "Map.h"
#include "Pioneers.h"
#include "Forests.h"
#include "Forest.h"
#include <queue>

static const int WIDTH  = 4;
static const int HEIGHT = 3;
static const int SEARCH_RANGE = 200;

Bulletin::Bulletin( MapPtr map, ForestsConstPtr forests, PioneersPtr pioneers ) :
Facility( CHIP_TYPE_BULLETIN, WIDTH, HEIGHT, map ) {
	_max = 1;
	_num = 0;
	_isAwake = true;

	_pioneers = pioneers;
	_forests = forests;
	_map = map;
}

Bulletin::~Bulletin( ) {

}

void Bulletin::update( ) {
	ForestPtr forest = _forests->get( _target );
		if ( _isAwake ) {
		_root = searchRoot( );
		_isAwake = false;
	}
	if ( _max > _num ) {
		_pioneers->create( _root, forest );
		_num++;
	}
	if ( !forest->isExist( ) ) {
		deleteRoot( );
	}
}

std::vector< Coord > Bulletin::searchRoot( ) {
	std::vector< Coord > root;
	root.push_back( getPos( ) );

	//ルート検索
	const int DIR_NUM = 8;
	const Coord DIR[ DIR_NUM ] = {
		Coord(  0,  1 ),
		Coord(  1,  0 ),
		Coord(  0, -1 ),
		Coord( -1,  0 ),
		Coord(  1,  1 ),
		Coord( -1, -1 ),
		Coord( -1,  1 ),
		Coord(  1, -1 ),
	};
	bool went[ COORD_HEIGHT * COORD_WIDTH ] = { false };
	int target_id = -1;
	std::queue< std::vector< Coord > > que;
	que.push( root );
	went[ getPos( ).getIdx( ) ] = true;

	//工場から森まで
	while ( !que.empty( ) ) {
		std::vector< Coord > temp = que.front( );
		que.pop( );
		Coord pos = temp.back( );
		
		for ( int i = 0; i < DIR_NUM; i++ ) {
			Coord after_pos = Coord( pos.x + DIR[ i ].x, pos.y + DIR[ i ] .y );
			if ( after_pos.getIdx( ) == -1 ) {
				continue;
			}

			Map::Chip chip = _map->getChip( after_pos );
			if ( chip.type == CHIP_TYPE_FOREST ) {
				ForestPtr forest = _forests->get( chip.value );
				if ( !forest->isTarget( ) ) {
					temp.push_back( after_pos );
					root = temp;
					target_id = chip.value;
					break;
				}
			}

			if ( chip.type != CHIP_TYPE_NONE ) {
				continue;
			}

			if ( went[ after_pos.getIdx( ) ] ) {
				continue;
			}
			std::vector< Coord > push = temp;
			push.push_back( after_pos );
			went[ after_pos.getIdx( ) ] = true;
			que.push( push );
		}
		if ( target_id != -1 ) {
			break;
		}
	}
	
	//ターゲットにたどり着かなかったら返す。
	if ( root.size( ) == 1 ) {
		return root;
	}
	//wentリセット
	for ( int i = 0; i < COORD_HEIGHT * COORD_WIDTH; i++ ) {
		went[ i ] = false;
	}
	//queueのリセット
	while( !que.empty( ) ) {
		que.pop( );
	}
	que.push( root );

	for ( int i = 1; i < ( int )root.size( ); i++ ) {
		went[ root[ i ].getIdx( )  ] = true;
	}
	
	//森から工場まで
	while ( !que.empty( ) ) {
		std::vector< Coord > temp = que.front( );
		que.pop( );
		Coord pos = temp.back( );
		for ( int i = 0; i < DIR_NUM; i++ ) {
			Coord after_pos = Coord( pos.x + DIR[ i ].x, pos.y + DIR[ i ] .y );
			if ( after_pos.getIdx( ) == getPos( ).getIdx( ) ) {
				root = temp;
				ForestPtr forest = _forests->get( target_id );
				forest->setTargetFlag( true );
				_target = target_id;
				return root;
			}
			if ( after_pos.getIdx( ) == -1 ) {
				continue;
			}
			Map::Chip chip = _map->getChip( after_pos );
			if ( chip.type != CHIP_TYPE_NONE ) {
				continue;
			}
			if ( went[ after_pos.getIdx( ) ] ) {
				continue;
			}
			std::vector< Coord > push = temp;
			push.push_back( after_pos );
			went[ after_pos.getIdx( ) ] = true;
			que.push( push );
		}
	}
	if ( que.empty( ) ) {
		root.clear( );
		root.push_back( getPos( ) );
	}
	return root;
}

Coord Bulletin::getPos( ) const {
	return Coord( getCoord( ).x + 1, getCoord( ).y + 3 );
}

void Bulletin::installRoot( unsigned char value ) {
	Map::Chip chip;
	chip.type = CHIP_TYPE_ROOT;
	chip.value = value;
	for ( int i = 0; i < ( int )_root.size( ); i++ ) {
		Map::Chip before = _map->getChip( _root[ i ] );
		if ( before.type == CHIP_TYPE_NONE ) {
			_map->setChip( _root[ i ], chip );
		}
	}
}

void Bulletin::deleteRoot( ) {
	_root.clear( );
	Map::Chip chip;
	chip.type = CHIP_TYPE_NONE;
	chip.value = 0;
	for ( int i = 0; i < ( int )_root.size( ); i++ ) {
		Map::Chip after = _map->getChip( _root[ i ] );
		if ( after.type == CHIP_TYPE_ROOT ) {
			_map->setChip( _root[ i ], chip );
		}
	}
}

std::vector< Coord > Bulletin::getRoot( ) const {
	return _root;
}