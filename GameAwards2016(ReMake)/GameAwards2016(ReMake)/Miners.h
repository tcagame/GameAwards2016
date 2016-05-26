#pragma once
#include "smart_ptr.h"
#include "Coord.h"
#include <array>
#include <vector>

PTR( Miners );
PTR( Miner );

class Miners {
public:
	Miners( );
	virtual ~Miners( );
public:
	void update( );
	bool create( const std::vector< Coord >& root, const Coord& target_pos );
	int getSize( );
	MinerPtr get( int idx );
private:
	static const int NUM = 100;
private:
	std::array< MinerPtr, NUM > _array;
	int _idx;
};

