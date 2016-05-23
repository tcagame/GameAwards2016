#pragma once
#include "Facility.h"
#include <vector>

PTR( PioneerFactory );
PTR( Map );

class PioneerFactory : public Facility {
public:
	PioneerFactory( MapPtr map );
	virtual ~PioneerFactory();
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