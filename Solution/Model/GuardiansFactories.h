#pragma once
#include "smart_ptr.h"
#include "Coord.h"
#include <array>

PTR( GuardiansFactories );
PTR( GuardiansFactory );
PTR( Map );

class GuardiansFactories {
public:
	GuardiansFactories( MapPtr map );
	virtual ~GuardiansFactories( );
public:
	int getSize( ) const;
	GuardiansFactoryPtr get( int idx ) const;
	void install( const Coord& coord );
	void update( );
private:
	static const int NUM = 100;
private:
	std::array< GuardiansFactoryPtr, NUM > _array;
	int _idx;
};

