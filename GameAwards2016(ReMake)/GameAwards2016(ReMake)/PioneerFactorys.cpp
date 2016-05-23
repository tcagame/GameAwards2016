#include "PioneerFactorys.h"
#include "PioneerFactory.h"

PioneerFactorys::PioneerFactorys( MapPtr map ) {
	for ( int i = 0; i < NUM; i++ ) {
		_array[ i ] = PioneerFactoryPtr( new PioneerFactory( map ) );
	}
	_idx = 0;
}

PioneerFactorys::~PioneerFactorys( ) {
}

void PioneerFactorys::update( ) {
	for ( int i = 0; i < _idx; i++ ) {
		_array[ i ]->update( );
	}
}

int PioneerFactorys::getSize( ) const {
	return _idx;
}

PioneerFactoryPtr PioneerFactorys::get( int idx ) const {
	return _array[ idx ];
}

void PioneerFactorys::install( const Coord& coord ) {
	if ( _idx >= NUM ) {
		return;
	}
	PioneerFactoryPtr miners_factory = _array[ _idx ];
	if ( miners_factory->install( coord, _idx ) ) {
		_idx++;
	}
}