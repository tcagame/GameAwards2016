#pragma once
#include "RatioCoord.h"
#include "smart_ptr.h"
#include "Coord.h"
#include "Ratio.h"

PTR( Packet );

class Packet {
public:
	Packet( const Coord& coord, const Ratio& x, const Ratio& y );
	virtual ~Packet( );
public:
	Coord getCoord( );
	Ratio getRatioX( );
	Ratio getRatioY( );
	unsigned char getNextDir( );
	void update( );
	bool isMoveNextCoord( );
	void setDir( unsigned char next_dir, unsigned char line_dir );
private:
	Coord _before_coord;
	RatioCoord _ratio_coord;
	unsigned char _next_dir;
	unsigned char _line_dir;
	bool _is_center_chip;
};

