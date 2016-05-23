#pragma once
#include "Facility.h"
#include <vector>

PTR( MinersFactory );
PTR( Map );

class MinersFactory : public Facility {
public:
	MinersFactory( MapPtr map );
	virtual ~MinersFactory( );
public:
	void update( );
	bool install( const Coord& coord, unsigned char value );
	Coord getPos( ) const;
	std::vector< Coord > getRoot( ) const;
private:
	std::vector< Coord > searchRoot( );
	void rootInstall( unsigned char value );
private:
	int _num;
	int _max;
	std::vector< Coord > _root;
	int _target;
};

