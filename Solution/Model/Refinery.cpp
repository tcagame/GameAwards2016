#include "Refinery.h"
#include "Chip.h"
#include "Map.h"
#include "Miners.h"
#include "GoldMines.h"
#include "GoldMine.h"
#include <queue>

static const int WIDTH  = 4;
static const int HEIGHT = 3;
static const int SEARCH_RANGE = 200;

Refinery::Refinery( MapPtr map, GroundConstPtr ground, GoldMinesConstPtr goldmines, MinersPtr miners ) :
Facility( CHIP_TYPE_REFINERY, WIDTH, HEIGHT, map, ground ) {
	_max = 1;
	_num = 0;
	_isAwake = true;

	_goldmines = goldmines;
	_miners = miners;
	_map = map;
	_ground = ground;
}

Refinery::~Refinery( ) {

}

void Refinery::update( ) {
	GoldMinePtr goldmine = _goldmines->get( _target );
	if ( _isAwake ) {
		_root = searchRoot( );
		_isAwake = false;
	}
	if ( _max > _num ) {
		_miners->create( _root, goldmine );
		_num++;
	}

	if ( !goldmine->isExist( ) ) {
		deleteRoot( );
	}
}


std::vector< Coord > Refinery::searchRoot( ) {
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
	int gold_mine_id = -1;
	std::queue< std::vector< Coord > > que;
	que.push( root );
	went[ getPos( ).getIdx( ) ] = true;

	//工場から金山まで
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
			if ( chip.type == CHIP_TYPE_GOLD_MINE ) {
				GoldMinePtr gold_mine = _goldmines->get( chip.value );
				if ( !gold_mine->isTarget( ) ) {
					temp.push_back( after_pos );
					root = temp;
					gold_mine_id = chip.value;
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
		if ( gold_mine_id != -1 ) {
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
	
	//金山から工場まで
	while ( !que.empty( ) ) {
		std::vector< Coord > temp = que.front( );
		que.pop( );
		Coord pos = temp.back( );
		for ( int i = 0; i < DIR_NUM; i++ ) {
			Coord after_pos = Coord( pos.x + DIR[ i ].x, pos.y + DIR[ i ] .y );
			if ( after_pos.getIdx( ) == getPos( ).getIdx( ) ) {
				root = temp;
				GoldMinePtr gold_miner = _goldmines->get( gold_mine_id );
				gold_miner->setTargetFlag( true );
				_target = gold_mine_id;
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

Coord Refinery::getPos( ) const {
	return Coord( getCoord( ).x + 1, getCoord( ).y + 3 );
}

void Refinery::installRoot( unsigned char value ) {
	Map::Chip chip;
	chip.type = CHIP_TYPE_ROOT;
	chip.value = value;
	for ( int i = 0; i < ( int )_root.size( ); i++ ) {
		Map::Chip after = _map->getChip( _root[ i ] );
		if ( after.type == CHIP_TYPE_NONE ) {
			_map->setChip( _root[ i ], chip );
		}
	}
}

void Refinery::deleteRoot( ) {
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

std::vector< Coord > Refinery::getRoot( ) const {
	return _root;
}