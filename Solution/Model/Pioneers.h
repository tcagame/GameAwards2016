#pragma once
#include "smart_ptr.h"
#include "Coord.h"
#include <array>
#include <vector>

PTR( Pioneers );
PTR( Pioneer );

PTR( UnitMap );
PTR( Forest );

class Pioneers {
public:
	Pioneers( UnitMapPtr unit_map );
	virtual ~Pioneers( );
public:
	void update( );
	bool create( const std::vector< Coord >& root, ForestPtr forest );
	int getSize( ) const;
	PioneerPtr get( int idx ) const;
private:
	static const int NUM = 100;
private:
	std::array< PioneerPtr, NUM > _array;
	UnitMapPtr _unit_map;
	int _idx;
};

