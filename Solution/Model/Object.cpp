#include "Object.h"

Object::Object( ) :
_finished( false ) {

}

Object::Object( const Coord& coord ) :
_finished( false ),
_coord( coord ) {

}

Object::~Object( ) {
}

void Object::setCoord ( const Coord& coord ) {
	_coord = coord;
}

void Object::finish( ) {
	_finished = true;
}

bool Object::isFinished( ) const {
	return _finished;
}

Coord Object::getCoord( ) const {
	return _coord;
}
