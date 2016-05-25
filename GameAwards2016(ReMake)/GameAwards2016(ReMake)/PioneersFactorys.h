#pragma once
#include "smart_ptr.h"
#include "Coord.h"
#include <array>

PTR( PioneersFactorys );
PTR( PioneersFactory );
PTR( Map );

class PioneersFactorys {
public:
	PioneersFactorys( MapPtr map );
	virtual ~PioneersFactorys( );
public:
	int getSize( ) const;
	PioneersFactoryPtr get( int idx ) const;
	void install( const Coord& coord );
	void update( );
private:
	static const int NUM = 100;
private:
	std::array< PioneersFactoryPtr, NUM > _array;
	int _idx;
};