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
	bool create( const std::vector< Coord >& root, const Coord& target_pos );
	int getSize( ) const;
	PioneerPtr get( int idx ) const;
private:
	static const int NUM = 100;
private:
	std::array< PioneerPtr, NUM > _array;
	int _idx;
};

