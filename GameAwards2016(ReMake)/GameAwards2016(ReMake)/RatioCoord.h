#pragma once
#include "Ratio.h"
#include "Coord.h"
#include "smart_ptr.h"
#include "mathmatics.h"

PTR( RatioCoord );

class RatioCoord {
public:
	struct RatioPoint {
		Ratio x;
		Ratio y;
	};
public:
	RatioCoord( const Coord& pos );
	virtual ~RatioCoord( );
public:
	void increase( const Coord& vec );
	RatioPoint getRatio( ) const;
	Coord getCoord( ) const;
	Vector getCoordWithRatio( ) const;
private:
	Coord _coord;
	RatioPoint _ratio;
};