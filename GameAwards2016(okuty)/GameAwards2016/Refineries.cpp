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
