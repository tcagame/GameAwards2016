#pragma once

#include "Coord.h"
#include "smart_ptr.h"
#include <list>

PTR( Object );

class Object {
public:
	Object( );
	Object( const Coord& coord );
	virtual ~Object( );
public:
	virtual void update( ) = 0;
	bool isFinished( ) const;
	Coord getCoord( ) const;
protected:
	void setCoord( const Coord& coord );
	void finish( );
private:
	bool _finished;
	Coord _coord;
};

