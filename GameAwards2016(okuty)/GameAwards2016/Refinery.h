#pragma once

#include "Facility.h"

PTR( Refinery );
PTR( Map );

class Refinery : public Facility {
public:
	Refinery( MapPtr map );
	virtual ~Refinery( );
};

