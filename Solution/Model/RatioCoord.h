#pragma once
#include "Ratio.h"
#include "Coord.h"
#include "smart_ptr.h"
#include "mathmatics.h"

class RatioCoord {
public:
	struct RatioPoint {
		Ratio x;
		Ratio y;

		RatioPoint( ) : x( ), y( ) { }

		RatioPoint( Ratio x_, Ratio y_ ) : x( x_ ), y( y_ ) { }
	};
public:
	RatioCoord( const Coord& pos );
	RatioCoord( const Coord& pos, const Ratio& x, const Ratio& y );
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