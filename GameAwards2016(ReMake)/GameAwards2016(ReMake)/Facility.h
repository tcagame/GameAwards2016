#pragma once

#include "Object.h"
#include "Coord.h"
#include "Chip.h"
#include <vector>

PTR( Facility );
PTR( Map );

class Facility : public Object {
public:
	Facility( MapPtr map, int width, int height );
	virtual ~Facility( );
public:
	Coord getLineOutCoord( ) const;
	Coord getLineInCoord( ) const;
	void setConnectLineCoord( const Coord& coord );
	bool checkConnectLineCoord( );
	void deleteConnectLineCoord( const Coord& coord );
protected:
	bool install( const Coord& coord, CHIP_TYPE type, int value );
private:
	const int _width;
	const int _height;
	MapPtr _map;
	Coord _connect_coord_in;
	Coord _connect_coord_out;
};

