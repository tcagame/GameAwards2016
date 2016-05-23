#pragma once
#include "Object.h"
#include "smart_ptr.h"
#include "mathmatics.h"
#include <vector>

PTR( Character );

class Character : public Object {
public:
	Character( const Coord& pos, const std::vector<Coord>& root );
	virtual ~Character( );
public:
	void update( );
protected:
	virtual void action( ) = 0;
private:
	void move( );
	void getRootPoint( );
	Vector dirNomarize( const Vector& dir );
private:
	int _speed;
	std::vector< Coord > _root;
	Vector _target;
	int _target_key;
	int _time;
};

