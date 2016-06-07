#include "Pioneers.h"
#include "Pioneer.h"
#include "App.h"
#include "UnitMap.h"

Pioneers::Pioneers( ) {
	_idx = 0;
}

Pioneers::~Pioneers( ) {
}


void Pioneers::update( ) {
	AppPtr app = App::getTask( );
	UnitMapPtr unit_map = app->getUnitMap( );
	UnitMap::Chip none;
	UnitMap::Chip pioneer;
	none.type = CHARACTER_TYPE_NONE;
	none.value = 0;
	pioneer.type = CHARACTER_TYPE_PIONEER;

	for ( int i = 0; i < _idx; i++ ) {
		unit_map->setChip( _array[ i ]->getCoord( ), none );
		_array[ i ]->update( );
		pioneer.value = i;
		unit_map->setChip( _array[ i ]->getCoord( ), pioneer );
	}
}

int Pioneers::getSize( ) const{
	return _idx;
}

bool Pioneers::create( const std::vector< Coord >& root, const Coord& target_pos ) {
	if ( _idx < NUM ) {
		_array[ _idx ] = PioneerPtr( new Pioneer( root, target_pos ) );
		_idx++;
		return true;
	}
	return false;
}

PioneerPtr Pioneers::get( int idx ) const{
	return _array[ idx ];
}
