#include "MinersFactorys.h"
#include "MinersFactory.h"

MinersFactorys::MinersFactorys( MapPtr map ) {
	for ( int i = 0; i < NUM; i++ ) {
		_array[ i ] = MinersFactoryPtr( new MinersFactory( map ) );
	}
	_idx = 0;
}

MinersFactorys::~MinersFactorys( ) {
}

void MinersFactorys::update( ) {
	for ( int i = 0; i < _idx; i++ ) {
		_array[ i ]->update( );
	}
}

int MinersFactorys::getSize( ) const {
	return _idx;
}

MinersFactoryPtr MinersFactorys::get( int idx ) const {
	return _array[ idx ];
}

void MinersFactorys::install( const Coord& coord ) {
	if ( _idx >= NUM ) {
		return;
	}
	MinersFactoryPtr miners_factory = _array[ _idx ];
	if ( miners_factory->install( coord, _idx ) ) {
		_idx++;
	}
}