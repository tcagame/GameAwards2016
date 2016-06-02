#pragma once

#include "Facilities.h"

PTR( Refineries );
PTR( Map );

class Refineries : public Facilities {
public:
	Refineries( );
	virtual ~Refineries( );
private:
	virtual FacilityPtr createFacility( MapPtr map );
};

