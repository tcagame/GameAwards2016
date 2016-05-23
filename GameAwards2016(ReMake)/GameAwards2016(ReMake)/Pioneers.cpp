#include "Pioneers.h"
#include "Pioneer.h"

Pioneers::Pioneers( ) {
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

bool Pioneers::create( const Coord& pos, const std::vector< Coord >& root ) {
	if ( _idx < NUM ) {
		_array[ _idx ] = PioneerPtr( new Pioneer( pos, root ) );
		_idx++;
		return true;
	}
	return false;
}

PioneerPtr Pioneers::get( int idx ) {
	return _array[ idx ];
}
