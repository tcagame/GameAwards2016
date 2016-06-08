#pragma once
#include "smart_ptr.h"
#include "Coord.h"
#include <array>
#include <vector>

PTR( Guardians );
PTR( Guardian );

class Guardians {
public:
	Guardians( );
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
};

