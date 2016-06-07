#include "Enemy.h"
#include "App.h"
#include "Map.h"
#include "mathmatics.h"
#include "Character.h"
#include "Facility.h"
#include "PioneersFactorys.h"
#include "PioneersFactory.h"
#include "MinersFactory.h"
#include "MinersFactorys.h"
#include <queue>

const int WIDTH = 2;
const int HEIGHT = 2;
const int HP = 1000000;
static const int SEARCH_RANGE = 15;

Enemy::Enemy( const Coord& pos ) :
_width( WIDTH ),
_height( HEIGHT ),
_pos( pos ) {
	int RATIO_MAX = _pos.getRatio( ).x.RATIO_ACCURACY;
	_speed = RATIO_MAX / 10;
	_hp = HP;
	setCoord( pos );
	_target = _pos.getCoordWithRatio( );
}

Enemy::~Enemy( ) {
}

void Enemy::update( ) {
	move( );
	if ( !existFacility( ) ) {
		searchFacility( );
	}
	if ( existFacility( ) && isExist( ) ) {
		searchRoot( );
	}
}

void Enemy::getRootPoint( ) {
	if ( existFacility( ) ) {
		FacilityPtr facility = _facility.lock( );
		Coord fp = facility->getCoord( );
		_target = RatioCoord( fp ).getCoordWithRatio( );
		return;
	}

	if ( _root.empty( ) ) {
		_target = _pos.getCoordWithRatio( );
		return;
	}
	Coord target = Coord( ( int )_target.x, ( int )_target.y );
	if ( target.getIdx( ) == _pos.getCoord( ).getIdx( ) ) {
		int key;
		for ( int i = 0; i < ( int )_root.size( ); i++ ) {
			if ( _root[ i ].getIdx( ) == _pos.getCoord( ).getIdx( ) ) {
				key = i;
				key++;
				key %= ( int )_root.size( );
				break;
			}
		}
		_target = RatioCoord( _root[ key ] ).getCoordWithRatio( );
	}
}

void Enemy::move( ) {
	AppPtr app = App::getTask( );
	MapPtr map = app->getMap( );
	
	getRootPoint( );
	Vector dir = _target - _pos.getCoordWithRatio( );
	Vector vec = dir.normalize( ) * _speed;
	_pos.increase( Coord( ( int )vec.x, ( int )vec.y ) );
	setCoord( _pos.getCoord( ) );
}

bool Enemy::isExist( ) {
	if ( _hp <= 0 ) {
		return false;
	}
	return true;
}

bool Enemy::existFacility( ) {
	return !_facility.expired( );
}


void Enemy::searchFacility( ) {
	AppPtr app = App::getTask( );
	MapPtr map = app->getMap( );
	Coord idx;
	for ( int i = 0; i < ( SEARCH_RANGE * SEARCH_RANGE ); i++ ) {
		idx.x = _pos.getCoord( ).x + ( i % SEARCH_RANGE ) - SEARCH_RANGE / 2;
		idx.y = _pos.getCoord( ).y + ( i / SEARCH_RANGE ) - SEARCH_RANGE / 2;
		if ( idx.x < 0 ) {
			idx.x = 0;
		}
		if ( idx.y < 0 ) {
			idx.y = 0;
		}

		Map::Chip chip = map->getChip( idx );
		if ( chip.type == CHIP_TYPE_MINER ) {
			MinersFactorysPtr miners_factories = app->getMinersFactorys( );
			MinersFactoryPtr miners_factory = miners_factories->get( chip.value );
			_facility = miners_factory;
		}
		if ( chip.type == CHIP_TYPE_PIONEER ) {
			PioneersFactorysPtr pioneers_factories = app->getPioneersFactorys( );
			PioneersFactoryPtr pioneers_factory = pioneers_factories->get( chip.value );
			_facility = pioneers_factory;
		}
	}
}

void Enemy::searchRoot( ) {
	std::vector< Coord > root;
	root.push_back( _pos.getCoord( ) );

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
	PioneersFactorysPtr pioneers_factories = app->getPioneersFactorys( );
	int pioneers_factory_id = -1;
	int miners_factory_id = -1;
	std::queue< std::vector< Coord > > que;
	que.push( root );
	went[ _pos.getCoord( ).getIdx( ) ] = true;


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
			if ( chip.type == CHIP_TYPE_MINER ) {
				temp.push_back( after_pos );
				root = temp;
				miners_factory_id = chip.value;
				break;
			}
			if ( chip.type == CHIP_TYPE_PIONEER ) {
				temp.push_back( after_pos );
				root = temp;
				pioneers_factory_id = chip.value;
				break;
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
		if ( pioneers_factory_id != -1 ) {
			break;
		}
		if ( miners_factory_id != -1 ) {
			break;
		}
	}
	
	//ターゲットにたどり着かなかったら返す。
	if ( root.size( ) == 1 ) {
		_root = root;
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

	_root = root;
}

RatioCoord Enemy::getRatioCoord( ) {
	return _pos;
}