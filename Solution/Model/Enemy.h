#pragma once
#include "Object.h"
#include "smart_ptr.h"
#include "RatioCoord.h"
#include <vector>

PTR( Enemy );
PTR( Facility );

class Enemy : public Object {
public:
	Enemy( const Coord& pos );
	virtual ~Enemy();
public:
	void update( );
	bool isExist( );
	RatioCoord getRatioCoord( );
private:
	void getRootPoint( );
	void move( );
	void searchRoot( );
	bool existFacility( );
	void searchFacility( );
private:
	std::vector< Coord > _root;
	const int _width;
	const int _height;
	int _hp;
	int _speed;
	Vector _target;
	FacilityWeakPtr _facility;
	RatioCoord _pos;
};

