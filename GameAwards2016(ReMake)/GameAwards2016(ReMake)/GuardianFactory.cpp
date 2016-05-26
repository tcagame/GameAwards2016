#include "GuardianFactory.h"
#include "App.h"
#include "Map.h"
#include "mathmatics.h"
#include <queue>

static const int WIDTH = 4;
static const int HEIGHT = 3;
static const int SEARCH_RANGE = 5;
static const int DIV = 10;

GuardianFactory::GuardianFactory( MapPtr map ) :
Facility( map, WIDTH, HEIGHT ) {
	_max = 1;
	_num = 0;
}

GuardianFactory::~GuardianFactory( ) {
}

void GuardianFactory::update( ) {

}

bool GuardianFactory::install( const Coord& coord, unsigned char value ) {
	bool result = Facility::install( coord, CHIP_TYPE_MINER, value );
	if ( result ) {
		_root = searchRoot( );
		installRoot( value );
	}
	return result;
}

std::vector< Coord > GuardianFactory::searchRoot( ) {
	std::vector< Coord > root;
	Vector pos = Vector( getCoord( ).x, getCoord( ).y );
	Vector vec = pos + Vector( 0, SEARCH_RANGE, 0 );
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), PI2 / DIV );
	for ( int i = 0; i < DIV; i++ ) {
		root.push_back( Coord( ( int )vec.x, ( int )vec.y ) );
		vec = mat.multiply( vec );
	}
	return root;
}

Coord GuardianFactory::getPos( ) const {
	return Coord( getCoord( ).x + 1, getCoord( ).y + 3 );
}

void GuardianFactory::installRoot( unsigned char value ) {
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

void GuardianFactory::deleteRoot( ) {
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

std::vector< Coord > GuardianFactory::getRoot( ) const {
	return _root;
}