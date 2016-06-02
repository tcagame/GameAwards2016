#pragma once

#include "Object.h"
#include "Coord.h"
#include "Chip.h"
#include <vector>

PTR( Facility );
PTR( Map );

class Facility : public Object {
public:
	Facility( CHIP_TYPE type, int width, int height, MapPtr map );
	virtual ~Facility( );
public:
	void update( ) { }
	Coord getLineFixationLeft( ) const;
	Coord getLineFixationRight( ) const;
	Coord getExitCoord( const Coord& coord ) const;
	void destroy( const Coord& coord );
	bool install( const Coord& coord, unsigned char value );
private:
	const CHIP_TYPE _chip_type;
	const int _width;
	const int _height;
	MapPtr _map;
	Coord _connect_fixation_left;
	Coord _connect_fixation_right;
};

