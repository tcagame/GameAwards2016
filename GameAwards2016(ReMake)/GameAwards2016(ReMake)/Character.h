#pragma once
#include "Object.h"
#include "smart_ptr.h"
#include "mathmatics.h"
#include <vector>

PTR( Character );

class Character : public Object {
public:
	Character( const std::vector<Coord>& root, const Coord& target_pos );
	virtual ~Character( );
public:
	void update( );
protected:
	virtual void action( ) = 0;
private:
	void move( );
	void getRootPoint( );
	Vector dirNomarize( const Vector& dir );
	bool existMaterial( Coord pos );
private:
	int _speed;
	std::vector< Coord > _root;
	Vector _target;
	int _target_key;
	Coord _target_pos;
	int _time;
};

