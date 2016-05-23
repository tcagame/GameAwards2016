#pragma once

#include "smart_ptr.h"
#include <list>

PTR( Mgr );
PTR( Object );

class Mgr {
public:
	Mgr( );
	virtual ~Mgr( );
public:
	void update( );
	void add( ObjectPtr object );
protected:
	const std::list< ObjectPtr >& getObjects( ) const;
private:
	std::list< ObjectPtr > _objects;
};

