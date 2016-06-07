#pragma once
#include"smart_ptr.h"
#include "Coord.h"
#include "CharacterType.h"
#include <array>

PTR( UnitMap );

class UnitMap {
public:
	struct Chip {
		CHARACTER_TYPE type;
		unsigned char value;
	};
public:
	UnitMap( );
	virtual ~UnitMap( );
public:
	Chip getChip( const Coord& coord ) const;
	void setChip( const Coord& coord, const Chip& chip );
private:
	std::array< Chip, COORD_HEIGHT * COORD_WIDTH > _array;
};

