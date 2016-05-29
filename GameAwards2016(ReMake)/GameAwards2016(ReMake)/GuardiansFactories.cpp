#include "GuardiansFactories.h"
#include "GuardiansFactory.h"

GuardiansFactories::GuardiansFactories( MapPtr map ) {
	for ( int i = 0; i < NUM; i++ ) {
		_array[ i ] = GuardiansFactoryPtr( new GuardiansFactory( map ) );
	}
	_idx = 0;
}

GuardiansFactories::~GuardiansFactories( ) {
}

void GuardiansFactories::update( ) {
	for ( int i = 0; i < _idx; i++ ) {
		_array[ i ]->update( );
	}
}

int GuardiansFactories::getSize( ) const {
	return _idx;
}

GuardiansFactoryPtr GuardiansFactories::get( int idx ) const {
	return _array[ idx ];
}

void GuardiansFactories::install( const Coord& coord ) {
	if ( _idx >= NUM ) {
		return;
	}
	GuardiansFactoryPtr Guardians_factory = _array[ _idx ];
	if ( Guardians_factory->install( coord, _idx ) ) {
		_idx++;
	}
}