#include "Enemies.h"
#include "Enemy.h"
#include "UnitMap.h"

Enemies::Enemies( UnitMapPtr unit_map, MapPtr map, BulletinsPtr bulletins, RefineriesPtr refineries ) {
	_idx = 0;
	_unit_map = unit_map;
	_map = map;

	_bulletins = bulletins;
	_refineries = refineries;
}

Enemies::~Enemies( ) {
}

void Enemies::update( ) {
	UnitMap::Chip none;
	UnitMap::Chip enemy;
	none.type = CHARACTER_TYPE_NONE;
	none.value = 0;
	enemy.type = CHARACTER_TYPE_ENEMY;

	for ( int i = 0; i < _idx; i++ ) {
		_unit_map->setChip( _array[ i ]->getCoord( ), none );
		_array[ i ]->update( );
		enemy.value = i;
		_unit_map->setChip( _array[ i ]->getCoord( ), enemy );
	}
}

int Enemies::getSize( ) {
	return _idx;
}

bool Enemies::create( const Coord& pos ) {
	if ( _idx < NUM ) {
		_array[ _idx ] = EnemyPtr( new Enemy( pos, _map, _bulletins, _refineries, _unit_map ) );
		_idx++;
		return true;
	}
	return false;
}

EnemyPtr Enemies::get( int idx ) {
	return _array[ idx ];
}
