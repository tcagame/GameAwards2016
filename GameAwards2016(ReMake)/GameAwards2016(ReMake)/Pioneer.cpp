#include "Pioneer.h"
#include "App.h"
#include "Map.h"
#include "Forests.h"
#include "Forest.h"

static const int POWER = 1000;

static const Coord FACTORY_DIFF = Coord( 1, 3 );

Pioneer::Pioneer( const Coord& pos, const std::vector< Coord >& root ) :
Character( pos, root ) {
	_pop_point = root.front( );
	_is_attack = false;
}

Pioneer::~Pioneer( ) {
}

void Pioneer::action( ) {
	AppPtr app = App::getTask( );
	MapPtr map = app->getMap( );
	Map::Chip chip = map->getChip( getCoord( ) );
	if ( chip.type == CHIP_TYPE_FOREST && !_is_attack ) {
		ForestsPtr forests = app->getForests( );
		ForestPtr forest = forests->get( chip.value );
		forest->attack( POWER );
		_is_attack = true;
	}
	if ( getCoord( ).getIdx( ) == _pop_point.getIdx( ) ) {
		_is_attack = false;
	}
}