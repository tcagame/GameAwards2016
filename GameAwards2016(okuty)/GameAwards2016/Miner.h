#pragma once
#include "Character.h"
#include "smart_ptr.h"
#include <vector>

PTR( Miner );

class Miner : public Character {
public:
	Miner( const std::vector< Coord >& root, const Coord& target_pos );
	virtual ~Miner( );
private:
	void action( );
	int _gold;
	Coord _pop_point; 
};

