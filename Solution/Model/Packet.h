#pragma once
#include "smart_ptr.h"
#include "Coord.h"
#include "Ratio.h"

PTR( Packet );

class Packet {
public:
	Packet( const Coord& coord );
	virtual ~Packet( );
public:
	Coord getCoord( );
	Ratio getRatioX( );
	Ratio getRatioY( );
	void update( );
private:
	Coord _coord;
};

