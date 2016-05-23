#include "Pioneer.h"
#include "App.h"
#include "Map.h"
#include "GoldMines.h"
#include "GoldMine.h"

static const int POWER = 1000;

static const Coord FACTORY_DIFF = Coord( 1, 3 );

Pioneer::Pioneer( const Coord& pos, const std::vector< Coord >& root ) :
Character( pos, root ) {
	_pop_point = root.front( );
}

Pioneer::~Pioneer( ) {
}

void Pioneer::action( ) {
}