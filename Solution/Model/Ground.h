#pragma once
#include "Coord.h"
#include "GroundChip.h"
#include "smart_ptr.h"
#include <array>

PTR( Ground );

class Ground {
public:
	Ground( );
	virtual ~Ground( );
public:
	GROUND_CHIP_TYPE getGroundChip( const Coord& coord ) const;
	GROUND_CHIP_TYPE getGroundChip( int idx ) const;
	void setGroundChip( const Coord& coord, const GROUND_CHIP_TYPE& ground_chip );
	void setGroundChip( int idx, const GROUND_CHIP_TYPE& ground_chip );
private:
	std::array< GROUND_CHIP_TYPE, COORD_WIDTH * COORD_HEIGHT > _data;
};


