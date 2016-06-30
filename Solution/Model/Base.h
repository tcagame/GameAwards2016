#pragma once

#include "Facility.h"
#include <vector>


PTR( Base );
PTR( Map );
PTR( Ground );
PTR( Enemy );

PTR( Guardians );
PTR( Enemies );

class Base : public Facility {
public:
	Base( MapPtr map, GroundConstPtr ground, GuardiansPtr guardians, EnemiesPtr enemies );
	virtual ~Base( );
public:
	void update( );
	Coord getPos( ) const;
	std::vector< Coord > getRoot( ) const;
	bool inEnemy( );
	EnemyPtr getTargetEnemy( );
private:
	std::vector< Coord > searchRoot( );
	void searchEnemy( );
	void installRoot( unsigned char value );
	void deleteRoot( );
private:
	int _num;
	int _max;
	std::vector< Coord > _root;
	EnemyWeakPtr _enemy;

	bool _isAwake;
	GuardiansPtr _guardians;
	EnemiesPtr _enemies;
	MapPtr _map;
	GroundConstPtr _ground;
};

