#pragma once

#include "Facility.h"

PTR( Base );
PTR( Map );

class Base : public Facility {
public:
	Base( MapPtr map );
	virtual ~Base( );
};

