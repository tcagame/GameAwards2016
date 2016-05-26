#include "PioneersFactory.h"
#include "App.h"
#include "Map.h"
#include "Pioneers.h"
#include "Forests.h"
#include "Forest.h"
#include <queue>

static const int WIDTH = 4;
static const int HEIGHT = 3;
static const int SEARCH_RANGE = 200;

PioneersFactory::PioneersFactory( MapPtr map ) :
Facility( map, WIDTH, HEIGHT ) {
	_max = 1;
	_num = 0;
}

PioneersFactory::~PioneersFactory() {
}

void PioneersFactory::update( ) {
	AppPtr app = App::getTask( );
	ForestsPtr forests = app->getForests( );
	ForestPtr forest = forests->get( _target );
	if ( _max > _num ) {
		PioneersPtr pioneers = app->getPioneers( );
		pioneers->create( _root, forest->getCoord( ) );
		_num++;
	}
	if ( !forest->isExist( ) ) {
		deleteRoot( );
	}
}

bool PioneersFactory::install( const Coord& coord, unsigned char value ) {
	bool result = Facility::install( coord, CHIP_TYPE_PIONEER, value );
	if ( result ) {
		_root = searchRoot( );
		installRoot( value );
	}
	return result;
}

std::vector< Coord > PioneersFactory::searchRoot( ) {
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
	AppPtr app = App::getTask( );
	MapPtr map = app->getMap( );
	ForestsPtr forests = app->getForests( );
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

			Map::Chip chip = map->getChip( after_pos );
			if ( chip.type == CHIP_TYPE_FOREST ) {
				ForestPtr forest = forests->get( chip.value );
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
				ForestPtr forest = forests->get( target_id );
				forest->setTargetFlag( true );
				_target = target_id;
				return root;
			}
			if ( after_pos.getIdx( ) == -1 ) {
				continue;
			}
			Map::Chip chip = map->getChip( after_pos );
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

Coord PioneersFactory::getPos( ) const {
	return Coord( getCoord( ).x + 1, getCoord( ).y + 3 );
}

void PioneersFactory::installRoot( unsigned char value ) {
	AppPtr app = App::getTask( );
	MapPtr map = app->getMap( );
	Map::Chip chip;
	chip.type = CHIP_TYPE_ROOT;
	chip.value = value;
	for ( int i = 0; i < ( int )_root.size( ); i++ ) {
		Map::Chip before = map->getChip( _root[ i ] );
		if ( before.type == CHIP_TYPE_NONE ) {
			map->setChip( _root[ i ], chip );
		}
	}
}

void PioneersFactory::deleteRoot( ) {
	AppPtr app = App::getTask( );
	MapPtr map = app->getMap( );
	Map::Chip chip;
	chip.type = CHIP_TYPE_NONE;
	chip.value = 0;
	for ( int i = 0; i < ( int )_root.size( ); i++ ) {
		Map::Chip after = map->getChip( _root[ i ] );
		if ( after.type == CHIP_TYPE_ROOT ) {
			map->setChip( _root[ i ], chip );
		}
	}
}

std::vector< Coord > PioneersFactory::getRoot( ) const {
	return _root;
}