#include "Bulletins.h"
#include "Bulletin.h"
#include "Map.h"

Bulletins::Bulletins( ForestsPtr forests, PioneersPtr pioneers ) {
	_pioneers = pioneers;
	_forests = forests;
}

Bulletins::~Bulletins( ) {
}

FacilityPtr Bulletins::createFacility( MapPtr map, GroundConstPtr ground ) {
	return BulletinPtr( new Bulletin( map, ground, _forests, _pioneers ) );
}

void Bulletins::update( ) {
	for ( int i = 0; i < ( int )getSize( ); i++ ) {
		BulletinPtr refinery = std::dynamic_pointer_cast< Bulletin >( get( i ) );
		refinery->update( );
	}
}