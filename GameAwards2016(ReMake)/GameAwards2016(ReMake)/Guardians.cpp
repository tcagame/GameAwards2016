#include "Guardians.h"
#include "Guardian.h"

Guardians::Guardians( ) {
	_idx = 0;
}

Guardians::~Guardians( ) {
}

void Guardians::update( ) {
	for ( int i = 0; i < _idx; i++ ) {
		_array[ i ]->update( );
	}
}

int Guardians::getSize( ) {
	return _idx;
}

bool Guardians::create( const std::vector< Coord >& root ) {
	if ( _idx < NUM ) {
		_array[ _idx ] = GuardianPtr( new Guardian( root ) );
		_idx++;
		return true;
	}
	return false;
}

GuardianPtr Guardians::get( int idx ) {
	return _array[ idx ];
}
