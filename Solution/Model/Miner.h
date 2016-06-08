#pragma once
#include "Character.h"
#include <vector>

PTR( Miner );
PTR( GoldMine );

class Miner : public Character {
public:
	Miner( const std::vector< Coord >& root, GoldMinePtr goldmine );
	virtual ~Miner( );
private:
	void action( );
	bool existMaterial( );
private:
	int _gold;
	Coord _pop_point; 
	GoldMinePtr _goldmine;
};

