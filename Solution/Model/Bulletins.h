#pragma once

#include "Facilities.h"

PTR( Bulletins );
PTR( Map );

PTR( Forests );
PTR( Pioneers );

class Bulletins : public Facilities {
public:
	Bulletins( ForestsPtr forests, PioneersPtr pioneers );
	virtual ~Bulletins( );
public:
	void update( );
private:	
	FacilityPtr createFacility( MapPtr map, GroundConstPtr ground );
private:
	ForestsPtr _forests;
	PioneersPtr _pioneers;
};

