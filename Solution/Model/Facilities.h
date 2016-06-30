#pragma once

#include "smart_ptr.h"
#include "Coord.h"
#include "chip.h"
#include <array>
#include <vector>

PTR( Facilities );
PTR( Facility );
PTR( Map );
PTR( Ground );

class Facilities  {
public:
	Facilities( );
	virtual ~Facilities( );
public:
	void initialize( MapPtr map, GroundConstPtr ground );
	int getSize( ) const;
	FacilityConstPtr get( int idx ) const;
	FacilityPtr get( int idx );
	void install( const Coord& coord );
	void relocation( const Coord& coord, unsigned char idx );
private:
	virtual FacilityPtr createFacility( MapPtr map, GroundConstPtr ground ) = 0;
private:
	static const int NUM = 10;
	std::array< FacilityPtr, NUM > _array;
	unsigned char _idx;
};

