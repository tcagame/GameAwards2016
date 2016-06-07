#pragma once

#include "Facility.h"

PTR( Bulletin );
PTR( Map );

class Bulletin : public Facility {
public:
	Bulletin( MapPtr map );
	virtual ~Bulletin( );
};

