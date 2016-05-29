#pragma once
#include "Facility.h"
#include <vector>

PTR( GuardiansFactory );
PTR( Map );

class GuardiansFactory : public Facility {
public:
	GuardiansFactory( MapPtr map );
	virtual ~GuardiansFactory( );
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

