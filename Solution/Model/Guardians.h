#pragma once
#include "smart_ptr.h"
#include "Coord.h"
#include <array>
#include <vector>

PTR( Guardians );
PTR( Guardian );

PTR( UnitMap );
PTR( Map );
PTR( Enemies );

class Guardians {
public:
	Guardians( UnitMapPtr unit_map, EnemiesPtr enemies, MapPtr map );
	virtual ~Guardians( );
public:
	void update( );
	bool create( const std::vector< Coord >& root, const Coord& factory_pos );
	int getSize( );
	GuardianPtr get( int idx );
private:
	static const int NUM = 100;
private:
	std::array< GuardianPtr, NUM > _array;
	int _idx;
	
	UnitMapPtr _unit_map;
	EnemiesPtr _enemies;
	MapPtr _map;
};

