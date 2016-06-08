#pragma once
#include "Facility.h"
#include <vector>

PTR( Bulletin );
PTR( Map );

PTR( Forests );
PTR( Pioneers );

class Bulletin : public Facility {
public:
	Bulletin( MapPtr map, ForestsConstPtr forests, PioneersPtr pioneers );
	virtual ~Bulletin( );
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

	ForestsConstPtr _forests;
	MapPtr _map;
	PioneersPtr _pioneers;
};

