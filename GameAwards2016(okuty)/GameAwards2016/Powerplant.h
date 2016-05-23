#pragma once

#include "Facility.h"
#include "Coord.h"
#include <vector>

PTR( Powerplant );

class Powerplant : public Facility {
public:
	Powerplant( MapPtr map );
	virtual ~Powerplant( );
public:
	Coord getLineOutCoord( ) const;
	Coord getLineInCoord( ) const;
private:
	bool _out_line_left;
};

