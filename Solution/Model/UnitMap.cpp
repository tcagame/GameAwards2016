#include "UnitMap.h"


UnitMap::UnitMap( ) {
	for ( int i = 0; i < COORD_WIDTH * COORD_HEIGHT; i++ ) {
		_array[ i ].type = CHARACTER_TYPE_NONE;
		_array[ i ].value = 0;
	}
}

UnitMap::~UnitMap( ) {
}

void UnitMap::setChip( const Coord& coord, const UnitMap::Chip& chip ) {
	_array[ coord.getIdx( ) ] = chip;
}

UnitMap::Chip UnitMap::getChip( const Coord& coord ) const {
	return _array[ coord.getIdx( ) ];
}


