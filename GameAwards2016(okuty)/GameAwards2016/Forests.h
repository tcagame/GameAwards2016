#pragma once
#include "smart_ptr.h"
#include "Coord.h"
#include <array>

PTR( Forests );
PTR( Forest );
PTR( Map );

class Forests {
public:
	Forests( MapPtr map );
	virtual ~Forests( );
public:
	bool install( const Coord& pos );
	ForestConstPtr get( int idx ) const;
	int getSize( ) const;
private:
	static const int NUM = 50;
private:
	int _idx;
	std::array< ForestPtr, NUM > _array;
};

