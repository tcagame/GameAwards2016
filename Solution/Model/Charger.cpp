#include "Charger.h"
#include "Chip.h"

static const int WIDTH  = 3;
static const int HEIGHT = 3;

Charger::Charger( MapPtr map, GroundConstPtr ground ) :
Facility( CHIP_TYPE_CHARGER, WIDTH, HEIGHT, map, ground ) {
	
}

Charger::~Charger( ) {

}
