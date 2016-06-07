#include "Miners.h"
#include "Miner.h"
#include "App.h"
#include "UnitMap.h"

Miners::Miners( ) {
	_idx = 0;
}

Miners::~Miners( ) {
}

void Miners::update( ) {
	AppPtr app = App::getTask( );
	UnitMapPtr unit_map = app->getUnitMap( );
	UnitMap::Chip none;
	UnitMap::Chip miner;
	none.type = CHARACTER_TYPE_NONE;
	none.value = 0;
	miner.type = CHARACTER_TYPE_MINER;

	for ( int i = 0; i < _idx; i++ ) {
		unit_map->setChip( _array[ i ]->getCoord( ), none );
		_array[ i ]->update( );
		miner.value = i;
		unit_map->setChip( _array[ i ]->getCoord( ), miner );
	}
}

int Miners::getSize( ) const{
	return _idx;
}

bool Miners::create( const std::vector< Coord >& root, const Coord& target_pos ) {
	if ( _idx < NUM ) {
		_array[ _idx ] = MinerPtr( new Miner( root, target_pos ) );
		_idx++;
		return true;
	}
	return false;
}

MinerConstPtr Miners::get( int idx ) const {
	return _array[ idx ];
}
