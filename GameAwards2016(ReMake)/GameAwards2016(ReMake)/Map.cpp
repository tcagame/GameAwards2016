#include "Map.h"
#include "Coord.h"
#include "DxLib.h"
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
	int idx = coord.getIdx( ); 
	return _data[ idx ];
}

void Map::setChip( const Coord& coord, const Chip& chip ) {
	int idx = coord.getIdx( ); 
	_data[ idx ] = chip;
}