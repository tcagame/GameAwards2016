#include "Mgr.h"
#include "Object.h"

Mgr::Mgr( ) {
}


Mgr::~Mgr( ) {
}

void Mgr::add( ObjectPtr object ) {
	_objects.push_back( object );
}

void Mgr::update( ) {
	std::list< ObjectPtr >::iterator ite = _objects.begin( );
	while ( ite != _objects.end( ) ) {
		ObjectPtr object = *ite;
		if ( object->isFinished( ) ) {
			ite = _objects.erase( ite );
		} else {
			object->update( );
			ite++;
		}
	}
}

const std::list< ObjectPtr >& Mgr::getObjects( ) const {
	return _objects;
}