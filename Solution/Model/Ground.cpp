#include "Ground.h"

Ground::Ground( ) {
	for ( int i = 0; i < COORD_WIDTH * COORD_HEIGHT; i++ ) {
		_data[ i ] = GROUND_CHIP_TYPE_MOUNTAIN;
	}
}

Ground::~Ground( ) {
}

GROUND_CHIP_TYPE Ground::getGroundChip( const Coord& coord ) const {
	return getGroundChip( coord.getIdx( ) );
}
GROUND_CHIP_TYPE Ground::getGroundChip( int idx ) const {
	return _data[ idx ];
}

void Ground::setGroundChip( const Coord& coord, const GROUND_CHIP_TYPE& ground_chip ) {
	setGroundChip( coord.getIdx( ), ground_chip );
}

void Ground::setGroundChip( int idx, const GROUND_CHIP_TYPE& ground_chip ) {
	_data[ idx ] = ground_chip;
}
