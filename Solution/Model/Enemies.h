#pragma once
#include "smart_ptr.h"
#include "Coord.h"
#include <array>
#include <vector>

PTR( Enemies );
PTR( Enemy );

PTR( UnitMap );
PTR( Bulletins );
PTR( Refineries );
PTR( Map );

class Enemies {
public:
	Enemies( UnitMapPtr unit_map, MapPtr map, BulletinsPtr bulletins, RefineriesPtr refineries );
	virtual ~Enemies( );
public:
	void update( );
	bool create( const Coord& pos );
	int getSize( );
	EnemyPtr get( int idx );
private:
	static const int NUM = 100;
private:
	std::array< EnemyPtr, NUM > _array;
	int _idx;

	UnitMapPtr _unit_map;
	MapPtr _map;
	BulletinsPtr _bulletins;
	RefineriesPtr _refineries;
};

