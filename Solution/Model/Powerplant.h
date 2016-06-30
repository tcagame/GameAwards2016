#pragma once

#include "Facility.h"
#include "Coord.h"
#include <vector>

PTR( Powerplant );

class Powerplant : public Facility {
public:
	Powerplant( MapPtr map, GroundConstPtr ground );
	virtual ~Powerplant( );
};

