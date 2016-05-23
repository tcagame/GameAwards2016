#include "Base.h"
#include "Chip.h"

static const int WIDTH  = 5;
static const int HEIGHT = 5;

Base::Base( MapPtr map ) :
Facility( CHIP_TYPE_BASE, WIDTH, HEIGHT, map ) {
	
}

Base::~Base( ) {

}
