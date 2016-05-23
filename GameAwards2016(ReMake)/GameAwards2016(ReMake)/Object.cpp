#include "Object.h"

Object::Object( ) {
}

Object::Object( const Coord& coord ) :
_coord( coord ) {
}

Object::~Object( ) {
}

void Object::setCoord ( const Coord& coord ) {
	_coord = coord;
}

Coord Object::getCoord( ) const {
	return _coord;
}
