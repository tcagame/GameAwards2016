#include "Chargers.h"
#include "Charger.h"
#include "Map.h"

Chargers::Chargers( ) {
}

Chargers::~Chargers( ) {
}

FacilityPtr Chargers::createFacility( MapPtr map ) {
	return ChargerPtr( new Charger( map ) );
}
