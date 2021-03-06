#include "Facilities.h"
#include "Facility.h"
#include "Ground.h"
#include "Map.h"

Facilities::Facilities( ) {
}

Facilities::~Facilities( ) {
}

void Facilities::initialize( MapPtr map, GroundConstPtr ground ) {
	for ( int i = 0; i < NUM; i++ ) {
		_array[ i ] = createFacility( map, ground );
	}
	_idx = 0;
}

void Facilities::install( const Coord& coord ) {
	if ( _idx >= NUM ) {
		return;
	}

	FacilityPtr facility = _array[ _idx ];
	if ( facility->install( coord, _idx ) ) {
		_idx++;
	}
}


void Facilities::relocation( const Coord& coord, unsigned char idx ) {
	if ( _idx >= NUM ) {
		return;
	}

	FacilityPtr facility = _array[ idx ];
	Coord deleteCoord = facility->getCoord( );
	if ( !facility->install( coord, idx ) ) {
		return;
	}
	facility->destroy( deleteCoord );
	
}

int Facilities::getSize( ) const {
	return _idx;
}

FacilityConstPtr Facilities::get( int idx ) const {
	return _array[ idx ];
}

FacilityPtr Facilities::get( int idx ) {
	return _array[ idx ];
}