#pragma once
#include "smart_ptr.h"
#include "Coord.h"
#include <array>

PTR( PioneerFactorys );
PTR( PioneerFactory );
PTR( Map );

class PioneerFactorys {
public:
	PioneerFactorys( MapPtr map );
	virtual ~PioneerFactorys( );
public:
	int getSize( ) const;
	PioneerFactoryPtr get( int idx ) const;
	void install( const Coord& coord );
	void update( );
private:
	static const int NUM = 100;
private:
	std::array< PioneerFactoryPtr, NUM > _array;
	int _idx;
};