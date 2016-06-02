#pragma once

#include "Facilities.h"

PTR( Bases );
PTR( Map );

class Bases : public Facilities {
public:
	Bases( );
	virtual ~Bases( );
private:
	virtual FacilityPtr createFacility( MapPtr map );
};

