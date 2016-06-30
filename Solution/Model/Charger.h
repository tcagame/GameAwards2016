#pragma once
#include "Facility.h"

PTR( Charger );
PTR( Map );
PTR( Ground );

class Charger : public Facility {
public:
	Charger( MapPtr map, GroundConstPtr ground );
	virtual ~Charger( );
};

