#include "GuardiansFactory.h"
#include "App.h"
#include "Map.h"
#include "mathmatics.h"
#include "Enemies.h"
#include "Enemy.h"
#include "Guardians.h"
#include "Guardian.h"
#include <queue>

static const int WIDTH = 3;
static const int HEIGHT = 3;
static const int SEARCH_RANGE = 7;
static const int DIV = SEARCH_RANGE * 16;

GuardiansFactory::GuardiansFactory( MapPtr map ) :
Facility( map, WIDTH, HEIGHT ) {
	_max = 1;
	_num = 0;
}

GuardiansFactory::~GuardiansFactory( ) {
}

void GuardiansFactory::update( ) {
	AppPtr app = App::getTask( );
	if ( _max > _num ) {
		GuardiansPtr guardians = app->getGuardians( );
		guardians->create( _root, getPos( ) );
		_num++;
	}
	if ( !_enemy.expired( ) ) {
		searchEnemy( );
	}
}

bool GuardiansFactory::install( const Coord& coord, unsigned char value ) {
	bool result = Facility::install( coord, CHIP_TYPE_GUARDIAN, value );
	if ( result ) {
		_root = searchRoot( );
		//installRoot( value );
	}
	return result;
}

std::vector< Coord > GuardiansFactory::searchRoot( ) {
	AppPtr app = App::getTask( );
	MapPtr map = app->getMap( );
	Map::Chip chip;
	std::vector< Coord > root;
	Vector pos = Vector( getPos( ).x, getPos( ).y );
	Vector dir = Vector( 1, 0 );
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), PI2 / DIV );
	for ( int i = 0; i < DIV; i++ ) {
		Vector vec = dir.normalize( ) * SEARCH_RANGE + pos;
		Coord target_pos = Coord( ( int )vec.x, ( int )vec.y );
		chip = map->getChip( target_pos );

		while ( chip.type != CHIP_TYPE_NONE && chip.type != CHIP_TYPE_GUARDIAN ) {
			double length = ( vec - pos ).getLength( );
			vec = dir.normalize( ) * ( length - 1 ) + pos;
			target_pos = Coord( ( int )vec.x, ( int )vec.y );
			chip = map->getChip( target_pos );
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

Coord GuardiansFactory::getPos( ) const {
	return Coord( getCoord( ).x + 2, getCoord( ).y + 2 );
}

void GuardiansFactory::installRoot( unsigned char value ) {
	AppPtr app = App::getTask( );
	MapPtr map = app->getMap( );
	Map::Chip chip;
	chip.type = CHIP_TYPE_ROOT;
	chip.value = value;
	for ( int i = 0; i < ( int )_root.size( ); i++ ) {
		Map::Chip after = map->getChip( _root[ i ] );
		if ( after.type == CHIP_TYPE_NONE ) {
			map->setChip( _root[ i ], chip );
		}
	}
}

void GuardiansFactory::deleteRoot( ) {
	_root.clear( );
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

std::vector< Coord > GuardiansFactory::getRoot( ) const {
	return _root;
}

void GuardiansFactory::searchEnemy( ) {
	AppPtr app = App::getTask( );
	EnemiesPtr enemies = app->getEnemies( );
	int min = SEARCH_RANGE;
	for ( int i = 0; i < enemies->getSize( ); i++ ) {
		EnemyPtr enemy = enemies->get( i );
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

bool GuardiansFactory::inEnemy( ) {
	return _enemy.expired( );
}

EnemyPtr GuardiansFactory::getTargetEnemy( ) {
	return _enemy.lock( );
}