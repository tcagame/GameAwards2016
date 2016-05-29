#pragma once

#include "Coord.h"
#include "Chip.h"
#include "smart_ptr.h"
#include <array>

PTR( Map );

class Map {
public:
	static Coord convScreenToPos( int sx, int sy );
public:
	struct Chip {
		unsigned char type;
		unsigned char value;
	};
public:
	Map();
	virtual ~Map();
public:
	Chip getChip( const Coord& coord ) const;
	Chip getChip( int idx ) const;
	void setChip( const Coord& coord, const Chip& chip );
	void setChip( int idx, const Chip& chip );
private:
	std::array< Chip, COORD_WIDTH * COORD_HEIGHT > _data;
};

