#include "Bases.h"
#include "Base.h"
#include "Map.h"

Bases::Bases( ) {
}

Bases::~Bases( ) {
}

FacilityPtr Bases::createFacility( MapPtr map ) {
	return BasePtr( new Base( map ) );
}
