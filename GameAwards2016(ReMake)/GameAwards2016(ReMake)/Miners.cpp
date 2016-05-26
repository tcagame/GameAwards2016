#include "Miners.h"
#include "Miner.h"

Miners::Miners( ) {
	_idx = 0;
}

Miners::~Miners( ) {
}

void Miners::update( ) {
	for ( int i = 0; i < _idx; i++ ) {
		_array[ i ]->update( );
	}
}

int Miners::getSize( ) {
	return _idx;
}

bool Miners::create( const std::vector< Coord >& root, const Coord& target_pos ) {
	if ( _idx < NUM ) {
		_array[ _idx ] = MinerPtr( new Miner( root, target_pos ) );
		_idx++;
		return true;
	}
	return false;
}

MinerPtr Miners::get( int idx ) {
	return _array[ idx ];
}
