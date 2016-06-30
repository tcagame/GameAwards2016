#include "Powerplant.h"
#include "Ground.h"
#include "Coord.h"
#include "Chip.h"

static const int WIDTH  = 5;
static const int HEIGHT = 3;

Powerplant::Powerplant( MapPtr map, GroundConstPtr ground ) :
Facility( CHIP_TYPE_POWERPLANT, WIDTH, HEIGHT, map, ground ) {

}

Powerplant::~Powerplant( ) {

}

