#include "Map.h"
#include "Coord.h"
#include "Chip.h"


Map::Map( ) {
	for ( int i = 0; i < COORD_WIDTH * COORD_HEIGHT; i++ ) {
		_data[ i ].type = CHIP_TYPE_NONE;
		_data[ i ].value = 0;
	}
}
Map::~Map( ) {
}

Map::Chip Map::getChip( const Coord& coord ) const {
	return getChip( coord.getIdx( ) );
}
Map::Chip Map::getChip( int idx ) const {
	return _data[ idx ];
}

void Map::setChip( const Coord& coord, const Chip& chip ) {
	setChip( coord.getIdx( ), chip );
}

void Map::setChip( int idx, const Chip& chip ) {
	_data[ idx ] = chip;
}
