#pragma once
#include "Object.h"
#include "smart_ptr.h"

PTR( Enemy );
PTR( Character );

class Enemy : public Object {
public:
	Enemy( const Coord& pos );
	virtual ~Enemy();
public:
	void update( );
	bool isExist( );
private:
	void move( );
	void searchTarget( );
private:
	const int _width;
	const int _height;
	int _hp;
	int _speed;
	CharacterWeakPtr _target;
};

