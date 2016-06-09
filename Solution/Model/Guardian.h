#pragma once
#include "Object.h"
#include "smart_ptr.h"
#include "mathmatics.h"
#include "RatioCoord.h"
#include <vector>

PTR( Guardian );
PTR( Enemy );

PTR( Map );
PTR( Enemies );
PTR( UnitMap )

class Guardian : public Object {
public:
	Guardian( const std::vector< Coord >& root, const Coord& factory_pos, EnemiesPtr enemies, MapPtr map, UnitMapPtr unit_map );
	virtual ~Guardian( );
public:
	void update( );
	RatioCoord getRatioCoord( );
private:
	void getRootPoint( );
	void move( );
	void action( );
	bool existEnemy( );
	void searchEnemy( );
private:
	std::vector< Coord > _root;
	Vector _target;
	int _speed;
	bool _is_attack;
	EnemyWeakPtr _enemy;
	RatioCoord _pos;
	RatioCoord _factory_pos;

	MapPtr _map;
	EnemiesPtr _enemies;
	UnitMapPtr _unit_map;
};