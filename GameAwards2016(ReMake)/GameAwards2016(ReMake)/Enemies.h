#pragma once
#include "smart_ptr.h"
#include "Coord.h"
#include <array>
#include <vector>

PTR( Enemies );
PTR( Enemy );

class Enemies {
public:
	Enemies( );
	virtual ~Enemies( );
public:
	void update( );
	bool create( const Coord& pos );
	int getSize( );
	EnemyPtr get( int idx );
private:
	static const int NUM = 100;
private:
	std::array< EnemyPtr, NUM > _array;
	int _idx;
};

