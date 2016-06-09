#pragma once
#include "Object.h"
#include "smart_ptr.h"
#include "RatioCoord.h"
#include <vector>

PTR( Enemy );
PTR( Facility );

PTR( Refineries );
PTR( Bulletins );
PTR( Map );
PTR( UnitMap );

class Enemy : public Object {
public:
	Enemy( const Coord& pos, MapPtr map, BulletinsPtr bulletins, RefineriesPtr refineries, UnitMapPtr unit_map );
	virtual ~Enemy();
public:
	void update( );
	bool isExist( );
	int getHP( ) const;
	void damage( int damage );
	void death( );
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
	bool _erased;

	MapPtr _map;
	RefineriesPtr _refineries;
	BulletinsPtr _bulletins;
	UnitMapPtr _unit_map;
};

