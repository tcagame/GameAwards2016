#pragma once

#include "Facilities.h"

PTR( Bulletins );
PTR( Map );

class Bulletins : public Facilities {
public:
	Bulletins( );
	virtual ~Bulletins( );
private:	
	FacilityPtr createFacility( MapPtr map );

};

