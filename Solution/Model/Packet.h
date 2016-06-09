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
	void nextChip( unsigned char dir_in, unsigned char dir_out );
	bool isWaiting( ) const;
	void set( const Coord& coord );
	void wait( );
	unsigned char getDirIn( ) const;
	unsigned char getDirOut( ) const;
private:
	Coord _coord;
	bool _waiting;
	unsigned char _dir_in;
	unsigned char _dir_out;
};

