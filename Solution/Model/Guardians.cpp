#include "Guardians.h"
#include "Guardian.h"
#include "UnitMap.h"


Guardians::Guardians( UnitMapPtr unit_map, EnemiesPtr enemies, MapPtr map ) {
	_idx = 0;
	_unit_map = unit_map;
	_map = map;
	_enemies = enemies;
}

Guardians::~Guardians( ) {
}

void Guardians::update( ) {
	UnitMap::Chip none;
	UnitMap::Chip gaudian;
	none.type = CHARACTER_TYPE_NONE;
	none.value = 0;
	gaudian.type = CHARACTER_TYPE_GAUDIAN;

	for ( int i = 0; i < _idx; i++ ) {
		_unit_map->setChip( _array[ i ]->getCoord( ), none );
		_array[ i ]->update( );
		gaudian.value = i;
		_unit_map->setChip( _array[ i ]->getCoord( ), gaudian );
	}
}

int Guardians::getSize( ) {
	return _idx;
}

bool Guardians::create( const std::vector< Coord >& root, const Coord& factory_pos ) {
	if ( _idx < NUM ) {
		_array[ _idx ] = GuardianPtr( new Guardian( root, factory_pos, _enemies, _map, _unit_map ));
		_idx++;
	}
		return true;
	return false;
}

GuardianPtr Guardians::get( int idx ) {
	return _array[ idx ];
}
