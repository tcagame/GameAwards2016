#pragma once
#include "Object.h"
#include "smart_ptr.h"
#include "mathmatics.h"
#include <vector>

PTR( Guardian );
PTR( Enemy );

class Guardian : public Object {
public:
	Guardian( const std::vector< Coord >& root );
	virtual ~Guardian( );
public:
	void update( );
private:
	void getRootPoint( );
	void move( );
	void action( );
	Vector dirNomarize( const Vector& dir );
	bool existEnemy( );
	void searchEnemy( );
private:
	std::vector< Coord > _root;
	Vector _target;
	int _speed;
	int _target_key;
	bool _is_attack;
	EnemyWeakPtr _enemy;

	int _time;
};