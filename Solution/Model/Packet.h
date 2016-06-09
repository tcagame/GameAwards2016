#pragma once
#include "RatioCoord.h"
#include "smart_ptr.h"
#include "Coord.h"

PTR( Packet );

class Packet {
public:
	Packet( );
	virtual ~Packet( );
public:
	Coord getCoord( );
	void nextChip( unsigned char dir );
	bool isWaiting( ) const;
	void set( const Coord& coord );
	void wait( );
private:
	Coord _coord;
	bool _waiting;
};

