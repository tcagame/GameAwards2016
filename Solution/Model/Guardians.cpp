#include "Guardians.h"
#include "Guardian.h"
#include "App.h"
#include "UnitMap.h"


Guardians::Guardians( ) {
	_idx = 0;
}

Guardians::~Guardians( ) {
}

void Guardians::update( ) {
	AppPtr app = App::getTask( );
	UnitMapPtr unit_map = app->getUnitMap( );
	UnitMap::Chip none;
	UnitMap::Chip gaudian;
	none.type = CHARACTER_TYPE_NONE;
	none.value = 0;
	gaudian.type = CHARACTER_TYPE_GAUDIAN;

	for ( int i = 0; i < _idx; i++ ) {
		unit_map->setChip( _array[ i ]->getCoord( ), none );
		_array[ i ]->update( );
		gaudian.value = i;
		unit_map->setChip( _array[ i ]->getCoord( ), gaudian );
	}
}

int Guardians::getSize( ) {
	return _idx;
}

bool Guardians::create( const std::vector< Coord >& root, const Coord& factory_pos ) {
	if ( _idx < NUM ) {
		_array[ _idx ] = GuardianPtr( new Guardian( root, factory_pos ) );
		_idx++;
	}
		return true;
	return false;
}

GuardianPtr Guardians::get( int idx ) {
	return _array[ idx ];
}
