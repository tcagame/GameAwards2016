#include "PioneersFactorys.h"
#include "PioneersFactory.h"

PioneersFactorys::PioneersFactorys( MapPtr map ) {
	for ( int i = 0; i < NUM; i++ ) {
		_array[ i ] = PioneersFactoryPtr( new PioneersFactory( map ) );
	}
	_idx = 0;
}

PioneersFactorys::~PioneersFactorys( ) {
}

void PioneersFactorys::update( ) {
	for ( int i = 0; i < _idx; i++ ) {
		_array[ i ]->update( );
	}
}

int PioneersFactorys::getSize( ) const {
	return _idx;
}

PioneersFactoryPtr PioneersFactorys::get( int idx ) const {
	return _array[ idx ];
}

void PioneersFactorys::install( const Coord& coord ) {
	if ( _idx >= NUM ) {
		return;
	}
	PioneersFactoryPtr miners_factory = _array[ _idx ];
	if ( miners_factory->install( coord, _idx ) ) {
		_idx++;
	}
}