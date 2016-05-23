#pragma once
#include "Character.h"
#include "smart_ptr.h"
#include <vector>

PTR( Miner );

class Miner : public Character {
public:
	Miner( const Coord& pos, const std::vector< Coord >& root );
	virtual ~Miner( );
private:
	void action( );
	int _gold;
	Coord _pop_point; 
};

