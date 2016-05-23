#include "Powerplant.h"
#include "Coord.h"
#include "Chip.h"

static const int WIDTH  = 5;
static const int HEIGHT = 3;

Powerplant::Powerplant( MapPtr map ) :
Facility( CHIP_TYPE_POWERPLANT, WIDTH, HEIGHT, map ) {
	_out_line_left = true;
}

Powerplant::~Powerplant( ) {

}


Coord Powerplant::getLineOutCoord( ) const {
	if ( _out_line_left ) {
		return Facility::getLineFixationLeft( );
	} else {
		return Facility::getLineFixationRight( );
	}
}

Coord Powerplant::getLineInCoord( ) const {
	if ( !_out_line_left ) {
		return Facility::getLineFixationLeft( );
	} else {
		return Facility::getLineFixationRight( );
	}
}
