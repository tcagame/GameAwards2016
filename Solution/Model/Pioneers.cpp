#include "Pioneers.h"
#include "Pioneer.h"
#include "UnitMap.h"

Pioneers::Pioneers( UnitMapPtr unit_map ) {
	_idx = 0;
	_unit_map = unit_map;
}

Pioneers::~Pioneers( ) {
}


void Pioneers::update( ) {
	UnitMap::Chip none;
	UnitMap::Chip pioneer;
	none.type = CHARACTER_TYPE_NONE;
	none.value = 0;
	pioneer.type = CHARACTER_TYPE_PIONEER;

	for ( int i = 0; i < _idx; i++ ) {
		_unit_map->setChip( _array[ i ]->getCoord( ), none );
		_array[ i ]->update( );
		pioneer.value = i;
		_unit_map->setChip( _array[ i ]->getCoord( ), pioneer );
	}
}

int Pioneers::getSize( ) const{
	return _idx;
}

bool Pioneers::create( const std::vector< Coord >& root, ForestPtr forest ) {
	if ( _idx < NUM ) {
		_array[ _idx ] = PioneerPtr( new Pioneer( root, forest ) );
		_idx++;
		return true;
	}
	return false;
}

PioneerPtr Pioneers::get( int idx ) const{
	return _array[ idx ];
}
