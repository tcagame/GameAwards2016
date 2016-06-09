#include "Base.h"
#include "Map.h"
#include "mathmatics.h"
#include "Enemies.h"
#include "Enemy.h"
#include "Guardians.h"
#include "Guardian.h"
#include "Chip.h"
#include <queue>

static const int WIDTH = 5;
static const int HEIGHT = 5;
static const int SEARCH_RANGE = 7;
static const int DIV = SEARCH_RANGE * 16;

Base::Base( MapPtr map, GuardiansPtr guardians, EnemiesPtr enemies ) :
Facility( CHIP_TYPE_BASE, WIDTH, HEIGHT, map ) {
	_max = 1;
	_num = 0;

	_isAwake = true;
	_guardians = guardians;
	_enemies = enemies;
	_map = map;
}

Base::~Base( ) {

}

void Base::update( ) {
	if ( _isAwake ) {
		_root = searchRoot( );
	}
	if ( _max > _num ) {
		_guardians->create( _root, getPos( ) );
		_num++;
	}
	if ( !_enemy.expired( ) ) {
		searchEnemy( );
	}
}

std::vector< Coord > Base::searchRoot( ) {
	Map::Chip chip;
	std::vector< Coord > root;
	Vector pos = Vector( getPos( ).x, getPos( ).y );
	Vector dir = Vector( 1, 0 );
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), PI2 / DIV );
	for ( int i = 0; i < DIV; i++ ) {
		Vector vec = dir.normalize( ) + pos;
		Coord target_pos = Coord( ( int )vec.x, ( int )vec.y );
		chip = _map->getChip( target_pos );

		while ( chip.type == CHIP_TYPE_NONE || chip.type == CHIP_TYPE_BASE ) {
			double length = ( vec - pos ).getLength( );
			if ( length + 1 > SEARCH_RANGE ) {
				break;
			}
			vec = dir.normalize( ) * ( length + 1 ) + pos;
			Coord temp = Coord( ( int )vec.x, ( int )vec.y );
			if ( temp.getIdx( )  == -1 ) {
				continue;
			}
			chip = _map->getChip( temp );
			if ( chip.type == CHIP_TYPE_NONE || chip.type == CHIP_TYPE_BASE ) {
				target_pos = temp;
			}
		}

		bool overlap = false;
		for ( int i = 0; i < ( int )root.size( ); i++ ) {
			if ( root[ i ].getIdx( ) == target_pos.getIdx( ) ) {
				overlap = true;
			}
		}

		dir = mat.multiply( dir );
		if ( overlap ) {
			continue;
		}
		root.push_back( target_pos );
	}
	return root;
}

Coord Base::getPos( ) const {
	return Coord( getCoord( ).x + 2, getCoord( ).y + 2 );
}

void Base::installRoot( unsigned char value ) {
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

void Base::deleteRoot( ) {
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

std::vector< Coord > Base::getRoot( ) const {
	return _root;
}

void Base::searchEnemy( ) {
	int min = SEARCH_RANGE;
	for ( int i = 0; i < _enemies->getSize( ); i++ ) {
		EnemyPtr enemy = _enemies->get( i );
		Vector ep = Vector( enemy->getCoord( ).x, enemy->getCoord( ).y );
		Vector pos = Vector( getCoord( ).x, getCoord( ).y );
		Vector vec = ep - pos;
		int length = ( int )vec.getLength( );
		if ( length <= min ) {
			_enemy = enemy;
			min = length;
		}
	}
}

bool Base::inEnemy( ) {
	return _enemy.expired( );
}

EnemyPtr Base::getTargetEnemy( ) {
	return _enemy.lock( );
}