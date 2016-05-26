#pragma once
#include "Facility.h"
#include <vector>

PTR( GuardianFactory );
PTR( Map );

class GuardianFactory : public Facility {
public:
	GuardianFactory( MapPtr map );
	virtual ~GuardianFactory( );
public:
	void update( );
	bool install( const Coord& coord, unsigned char value );
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
};

