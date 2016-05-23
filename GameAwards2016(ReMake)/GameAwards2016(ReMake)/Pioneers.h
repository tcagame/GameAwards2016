#pragma once
#include "smart_ptr.h"
#include "Coord.h"
#include <array>
#include <vector>

PTR( Pioneers );
PTR( Pioneer );

class Pioneers {
public:
	Pioneers( );
	virtual ~Pioneers( );
public:
	void update( );
	bool create( const Coord& pos, const std::vector< Coord >& root );
	int getSize( );
	PioneerPtr get( int idx );
private:
	static const int NUM = 100;
private:
	std::array< PioneerPtr, NUM > _array;
	int _idx;
};

