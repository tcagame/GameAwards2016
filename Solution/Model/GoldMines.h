#pragma once
#include "smart_ptr.h"
#include "Coord.h"
#include <array>

PTR( GoldMines );
PTR( GoldMine );
PTR( Map );

class GoldMines {
public:
	GoldMines( MapPtr map );
	virtual ~GoldMines( );
public:
	bool install( const Coord& pos );
	GoldMinePtr get( int idx ) const;
	int getSize( ) const;
private:
	static const int NUM = 50;
private:
	int _idx;
	std::array< GoldMinePtr, NUM > _array;
};

