#include "Bulletins.h"
#include "Bulletin.h"
#include "Map.h"

Bulletins::Bulletins( ) {
}

Bulletins::~Bulletins( ) {
}

FacilityPtr Bulletins::createFacility( MapPtr map ) {
	return BulletinPtr( new Bulletin( map ) );
}
