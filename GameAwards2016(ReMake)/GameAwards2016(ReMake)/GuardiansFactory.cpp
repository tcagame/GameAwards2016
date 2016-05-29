#include "GuardiansFactory.h"
#include "App.h"
#include "Map.h"
#include "mathmatics.h"
#include "Enemies.h"
#include "Enemy.h"
#include "Guardians.h"
#include "Guardian.h"
#include <queue>

static const int WIDTH = 4;
static const int HEIGHT = 3;
static const int SEARCH_RANGE = 2;
static const int DIV = 10;

GuardiansFactory::GuardiansFactory( MapPtr map ) :
Facility( map, WIDTH, HEIGHT ) {
	_max = 1;
	_num = 0;
}

GuardiansFactory::~GuardiansFactory( ) {
}

void GuardiansFactory::update( ) {
	AppPtr app = App::getTask( );
	EnemiesPtr enemies = app->getEnemies( );
	EnemyPtr enemy = enemies->get( _target );
	if ( _max > _num ) {
		GuardiansPtr guardians = app->getGuardians( );
		guardians->create( _root, enemy->getCoord( ) );
		_num++;
	}

	if ( !enemy->isExist( ) ) {
		deleteRoot( );
	}
}

bool GuardiansFactory::install( const Coord& coord, unsigned char value ) {
	bool result = Facility::install( coord, CHIP_TYPE_GUARDIAN, value );
	if ( result ) {
		_root = searchRoot( );
		installRoot( value );
	}
	return result;
}

std::vector< Coord > GuardiansFactory::searchRoot( ) {
	std::vector< Coord > root;
	//root.push_back( getPos( ) );
	Vector pos = Vector( getCoord( ).x, getCoord( ).y );
	Vector vec = pos + Vector( 0, SEARCH_RANGE, 0 );
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), 360 / DIV );
	for ( int i = 0; i < DIV; i++ ) {
		Coord test = Coord( ( int )vec.x, ( int )vec.y );
		if ( test.getIdx() != -1 ) {
			root.push_back( test );
		}
		vec = mat.multiply( vec.normalize ) + vec;
	}
	return root;
}

Coord GuardiansFactory::getPos( ) const {
	return Coord( getCoord( ).x + 1, getCoord( ).y + 3 );
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