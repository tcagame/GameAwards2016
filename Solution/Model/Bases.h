#pragma once

#include "Facilities.h"

PTR( Bases );
PTR( Map );

PTR( Enemies );
PTR( Guardians );

class Bases : public Facilities {
public:
	Bases( EnemiesPtr enemies, GuardiansPtr guardians );
	virtual ~Bases( );
public:
	void update( );
private:
	virtual FacilityPtr createFacility( MapPtr map );
private:
	EnemiesPtr _enemies;
	GuardiansPtr _guardians;
};

