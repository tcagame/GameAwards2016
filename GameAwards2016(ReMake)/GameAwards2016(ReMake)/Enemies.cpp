#include "Enemies.h"
#include "Enemy.h"

Enemies::Enemies( ) {
	_idx = 0;
}

Enemies::~Enemies( ) {
}

void Enemies::update( ) {
	for ( int i = 0; i < _idx; i++ ) {
		_array[ i ]->update( );
	}
}

int Enemies::getSize( ) {
	return _idx;
}

bool Enemies::create( const Coord& pos ) {
	if ( _idx < NUM ) {
		_array[ _idx ] = EnemyPtr( new Enemy( pos ) );
		_idx++;
		return true;
	}
	return false;
}

EnemyPtr Enemies::get( int idx ) {
	return _array[ idx ];
}
