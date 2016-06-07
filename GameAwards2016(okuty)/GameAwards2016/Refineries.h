#pragma once

#include "Facilities.h"

PTR( Refineries );
PTR( Map );

class Refineries : public Facilities {
public:
	Refineries( );
	virtual ~Refineries( );
public:
	void update( );
private:
	virtual FacilityPtr createFacility( MapPtr map );
};

