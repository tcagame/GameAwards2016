#pragma once
#include "smart_ptr.h"
#include "Coord.h"
#include <array>
#include <vector>

PTR( Miners );
PTR( Miner );

PTR( UnitMap );
PTR( GoldMine );

class Miners {
public:
	Miners( UnitMapPtr unit_map );
	virtual ~Miners( );
public:
	void update( );
	bool create( const std::vector< Coord >& root, GoldMinePtr goldmine );
	int getSize( ) const;
	MinerConstPtr get( int idx ) const;
private:
	static const int NUM = 100;
private:
	std::array< MinerPtr, NUM > _array;
	int _idx;
	UnitMapPtr _unit_map;
};

