#pragma once
#include "Facility.h"
#include <vector>

PTR( Bulletin );
PTR( Map );

class Bulletin : public Facility {
public:
	Bulletin( MapPtr map );
	virtual ~Bulletin( );
};

