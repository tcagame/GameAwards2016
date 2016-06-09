#include "Miners.h"
#include "Miner.h"
#include "UnitMap.h"

Miners::Miners( UnitMapPtr unit_map ) {
	_idx = 0;
	_unit_map = unit_map;
}

Miners::~Miners( ) {
}

void Miners::update( ) {
	UnitMap::Chip none;
	UnitMap::Chip miner;
	none.type = CHARACTER_TYPE_NONE;
	none.value = 0;
	miner.type = CHARACTER_TYPE_MINER;

	for ( int i = 0; i < _idx; i++ ) {
		_unit_map->setChip( _array[ i ]->getCoord( ), none );
		_array[ i ]->update( );
		miner.value = i;
		_unit_map->setChip( _array[ i ]->getCoord( ), miner );
	}
}

int Miners::getSize( ) const{
	return _idx;
}

bool Miners::create( const std::vector< Coord >& root, GoldMinePtr goldmine ) {
	if ( _idx < NUM ) {
		_array[ _idx ] = MinerPtr( new Miner( root, goldmine ) );
		_idx++;
		return true;
	}
	return false;
}

MinerConstPtr Miners::get( int idx ) const {
	return _array[ idx ];
}
