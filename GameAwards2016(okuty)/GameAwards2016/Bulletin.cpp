#include "Bulletin.h"
#include "Chip.h"

static const int WIDTH  = 4;
static const int HEIGHT = 3;

Bulletin::Bulletin( MapPtr map ) :
Facility( CHIP_TYPE_BULLETIN, WIDTH, HEIGHT, map ) {
	
}

Bulletin::~Bulletin( ) {

}
