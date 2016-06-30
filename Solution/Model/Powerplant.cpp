#include "Powerplant.h"
#include "Ground.h"
#include "Coord.h"
#include "Chip.h"
#include <assert.h>

static const int WIDTH  = 5;
static const int HEIGHT = 5;

Powerplant::Powerplant( MapPtr map, GroundConstPtr ground ) :
Facility( CHIP_TYPE_POWERPLANT, WIDTH, HEIGHT, map, ground ) {
	// î≠ìdèäÇÕç≈èâÇ©ÇÁê›íuÇ≥ÇÍÇƒÇ¢ÇÈ
	int mx = 0;
	int my = 0;

	bool find = false;
	for ( int i = 0; i < ground->getHeight( ) * ground->getWidth( ); i++ ) {
		mx = i % ground->getWidth( );
		my = i / ground->getWidth( );
		GROUND_CHIP_TYPE chip = ground->getType( mx, my );
		if ( chip == GROUND_CHIP_TYPE_POWERPLANT ) {
			find = true;
			break;
		}
	}
	if ( find ) {
		bool result_powerplant_installation = install( Coord( mx, my ), 0 );
		assert( result_powerplant_installation );
	}
	assert( find );
}

Powerplant::~Powerplant( ) {

}

