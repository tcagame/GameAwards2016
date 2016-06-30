#pragma once
#include "Facility.h"
#include <vector>

PTR( Refinery );
PTR( Map );
PTR( Ground );

PTR( GoldMines );
PTR( Miners );

class Refinery : public Facility {
public:
	Refinery( MapPtr map, GroundConstPtr ground, GoldMinesConstPtr goldmines, MinersPtr miner );
	virtual ~Refinery( );
public:
	void update( );
	Coord getPos( ) const;
	std::vector< Coord > getRoot( ) const;
private:
	std::vector< Coord > searchRoot( );
	void installRoot( unsigned char value );
	void deleteRoot( );
private:
	int _num;
	int _max;
	std::vector< Coord > _root;
	int _target;
	bool _isAwake;

	GoldMinesConstPtr _goldmines;
	MapPtr _map;
	GroundConstPtr _ground;
	MinersPtr _miners;
};

