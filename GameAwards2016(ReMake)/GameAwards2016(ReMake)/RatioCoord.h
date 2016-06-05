#pragma once
#include "Ratio.h"
#include "Coord.h"
#include "mathmatics.h"

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
	Coord getPos( ) const;
	Vector getCoordWithRatio( ) const;
private:
	Coord _pos;
	RatioPoint _ratio;
};