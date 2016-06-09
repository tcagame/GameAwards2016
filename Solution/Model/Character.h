#pragma once
#include "Object.h"
#include "smart_ptr.h"
#include "mathmatics.h"
#include "RatioCoord.h"
#include <vector>

PTR( Character );

class Character : public Object {
public:
	Character( const std::vector<Coord>& root );
	virtual ~Character( );
public:
	void update( );
	RatioCoord getRatioCoord( ) const;
protected:
	virtual void action( ) = 0;
	virtual bool existMaterial( ) = 0;
private:
	void move( );
	void getRootPoint( );
private:
	int _speed;
	std::vector< Coord > _root;
	Vector _root_point;
	RatioCoord _pop_point;
	RatioCoord _pos;
};

