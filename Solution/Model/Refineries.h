#pragma once

#include "Facilities.h"

PTR( Refineries );
PTR( Map );

PTR( GoldMines );
PTR( Miners );

class Refineries : public Facilities {
public:
	Refineries( GoldMinesPtr goldmines, MinersPtr miners );
	virtual ~Refineries( );
public:
	void update( );
private:
	virtual FacilityPtr createFacility( MapPtr map, GroundConstPtr ground );
private:
	GoldMinesPtr _goldmines;
	MinersPtr _miners;
};

