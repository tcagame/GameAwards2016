#include "Refinery.h"
#include "Chip.h"

static const int WIDTH  = 4;
static const int HEIGHT = 3;

Refinery::Refinery( MapPtr map ) :
Facility( CHIP_TYPE_REFINERY, WIDTH, HEIGHT, map ) {
	
}

Refinery::~Refinery( ) {

}
