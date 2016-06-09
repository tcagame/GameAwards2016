#include "Enemy.h"
#include "Map.h"
#include "mathmatics.h"
#include "Chip.h"
#include "Character.h"
#include "Facility.h"
#include "Bulletins.h"
#include "Refineries.h"
#include <queue>

const int WIDTH = 2;
const int HEIGHT = 2;
const int HP = 1000000;
static const int SEARCH_RANGE = 15;

Enemy::Enemy( const Coord& pos, MapPtr map, BulletinsPtr bulletins, RefineriesPtr refineries  ) :
_width( WIDTH ),
_height( HEIGHT ),
_pos( pos ) {
	int RATIO_MAX = _pos.getRatio( ).x.ACCURACY;
	_speed = RATIO_MAX / 10;
	_hp = HP;
	setCoord( pos );
	_target = _pos.getCoordWithRatio( );

	_map = map;
	_bulletins = bulletins;
	_refineries = refineries;
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

		Map::Chip chip = _map->getChip( idx );
		if ( chip.type == CHIP_TYPE_REFINERY ) {
			_facility = _refineries->get( chip.value );
		}
		if ( chip.type == CHIP_TYPE_BULLETIN ) {
			_facility = _bulletins->get( chip.value );
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
	int bulletin_id = -1;
	int refinery_id = -1;
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

			Map::Chip chip = _map->getChip( after_pos );
			if ( chip.type == CHIP_TYPE_REFINERY ) {
				temp.push_back( after_pos );
				root = temp;
				refinery_id = chip.value;
				break;
			}
			if ( chip.type == CHIP_TYPE_BULLETIN ) {
				temp.push_back( after_pos );
				root = temp;
				bulletin_id = chip.value;
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
		if ( bulletin_id != -1 ) {
			break;
		}
		if ( refinery_id != -1 ) {
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