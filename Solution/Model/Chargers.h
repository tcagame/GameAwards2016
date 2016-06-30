#pragma once

#include "Facilities.h"

PTR( Chargers );
PTR( Map );

class Chargers : public Facilities {
public:
	Chargers( );
	virtual ~Chargers( );
private:
	virtual FacilityPtr createFacility( MapPtr map, GroundConstPtr ground );
};

