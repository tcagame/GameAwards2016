#pragma once
#include "smart_ptr.h"
#include "Coord.h"
#include <array>

PTR( MinersFactorys );
PTR( MinersFactory );
PTR( Map );

class MinersFactorys {
public:
	MinersFactorys( MapPtr map );
	virtual ~MinersFactorys( );
public:
	int getSize( ) const;
	MinersFactoryPtr get( int idx ) const;
	void install( const Coord& coord );
	void update( );
private:
	static const int NUM = 100;
private:
	std::array< MinersFactoryPtr, NUM > _array;
	int _idx;
};

