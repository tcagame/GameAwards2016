#include "Refineries.h"
#include "Refinery.h"
#include "Map.h"

Refineries::Refineries( ) {
}

Refineries::~Refineries( ) {
}

FacilityPtr Refineries::createFacility( MapPtr map ) {
	return RefineryPtr( new Refinery( map ) );
}

void Refineries::update( ) {
	for ( int i = 0; i < ( int )getSize( ); i++ ) {
		RefineryPtr refinery = std::dynamic_pointer_cast< Refinery >( get( i ) );
		refinery->update( );
	}
}

