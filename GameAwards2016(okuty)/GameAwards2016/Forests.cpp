#include "Forests.h"
#include "Forest.h"

Forests::Forests( MapPtr map ) {
	for ( int i = 0; i < NUM; i++ ) {
		_array[ i ] = ForestPtr( new Forest( map ) );
	}
	_idx = 0;
}

Forests::~Forests( ) {

}

ForestPtr Forests::get( int idx ) {
	return _array[ idx ];
}

int Forests::getSize( ) const {
	return _idx;
}

bool Forests::install( const Coord& pos ) {
	if ( _idx >= NUM ) {
		return false;
	}
	ForestPtr forest = _array[ _idx ];
	if ( forest->install( pos, _idx ) ) {
		_idx++;
		return true;
	}
	return false;
}
