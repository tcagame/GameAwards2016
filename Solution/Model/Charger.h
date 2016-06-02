#pragma once
#include "Facility.h"

PTR( Charger );
PTR( Map );

class Charger : public Facility {
public:
	Charger( MapPtr map );
	virtual ~Charger( );
};

