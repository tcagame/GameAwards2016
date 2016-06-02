#include "Enemies.h"
#include "Enemy.h"
#include "App.h"
#include "UnitMap.h"

Enemies::Enemies( ) {
	_idx = 0;
}

Enemies::~Enemies( ) {
}

void Enemies::update( ) {
	AppPtr app = App::getTask( );
	UnitMapPtr unit_map = app->getUnitMap( );
	UnitMap::Chip none;
	UnitMap::Chip enemy;
	none.type = CHARACTER_TYPE_NONE;
	none.value = 0;
	enemy.type = CHARACTER_TYPE_ENEMY;

	for ( int i = 0; i < _idx; i++ ) {
		unit_map->setChip( _array[ i ]->getCoord( ), none );
		_array[ i ]->update( );
		enemy.value = i;
		unit_map->setChip( _array[ i ]->getCoord( ), enemy );
	}
}

int Enemies::getSize( ) {
	return _idx;
}

bool Enemies::create( const Coord& pos ) {
	if ( _idx < NUM ) {
		_array[ _idx ] = EnemyPtr( new Enemy( pos ) );
		_idx++;
		return true;
	}
	return false;
}

EnemyPtr Enemies::get( int idx ) {
	return _array[ idx ];
}
