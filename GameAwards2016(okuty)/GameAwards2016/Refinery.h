#pragma once
#include "Facility.h"
#include <vector>

PTR( Refinery );
PTR( Map );

class Refinery : public Facility {
public:
	Refinery( MapPtr map );
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
};

