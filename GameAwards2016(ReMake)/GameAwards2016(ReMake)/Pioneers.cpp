#include "Pioneers.h"
#include "Pioneer.h"

Pioneers::Pioneers( ) {
	_idx = 0;
}

Pioneers::~Pioneers( ) {
}

void Pioneers::update( ) {
	for ( int i = 0; i < _idx; i++ ) {
		_array[ i ]->update( );
	}
}

int Pioneers::getSize( ) {
	return _idx;
}

bool Pioneers::create( const std::vector< Coord >& root, const Coord& target_pos ) {
	if ( _idx < NUM ) {
		_array[ _idx ] = PioneerPtr( new Pioneer( root, target_pos ) );
		_idx++;
		return true;
	}
	return false;
}

PioneerPtr Pioneers::get( int idx ) {
	return _array[ idx ];
}
