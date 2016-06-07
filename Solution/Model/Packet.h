#pragma once
#include "RatioCoord.h"
#include "smart_ptr.h"
#include "Coord.h"
#include "Ratio.h"

PTR( Packet );

class Packet {
public:
	Packet( );
	virtual ~Packet( );
public:
	Coord getCoord( );
	Ratio getAnimationRatio( ) const;
	void update( );
	void nextChip( unsigned char dir );
	bool isWaiting( ) const;
	void set( const Coord& coord );
	void wait( );
	bool isFinishedAnimation( ) const;
private:
	Coord _coord;
	Ratio _animation_ratio;
	bool _waiting;
};

