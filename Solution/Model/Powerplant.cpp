#include "Powerplant.h"
#include "Coord.h"
#include "Chip.h"

static const int WIDTH  = 5;
static const int HEIGHT = 3;

Powerplant::Powerplant( MapPtr map ) :
Facility( CHIP_TYPE_POWERPLANT, WIDTH, HEIGHT, map ) {

}

Powerplant::~Powerplant( ) {

}


Coord Powerplant::getStartCoord( ) const {
	return Coord( Facility::getLineFixationLeft( ).x - 1, Facility::getLineFixationLeft( ).y );
}
