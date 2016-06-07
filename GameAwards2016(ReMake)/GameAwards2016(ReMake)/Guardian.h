#pragma once
#include "Object.h"
#include "smart_ptr.h"
#include "mathmatics.h"
#include "RatioCoord.h"
#include <vector>

PTR( Guardian );
PTR( Enemy );

class Guardian : public Object {
public:
	Guardian( const std::vector< Coord >& root, const Coord& factory_pos );
	virtual ~Guardian( );
public:
	void update( );
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
	RatioCoord _factory_pos;
	RatioCoord _pos;
	int _time;
};