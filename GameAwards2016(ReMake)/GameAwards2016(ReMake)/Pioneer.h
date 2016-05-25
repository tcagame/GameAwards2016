#pragma once
#include "Character.h"
#include "smart_ptr.h"
#include <vector>

PTR( Pioneer );

class Pioneer : public Character {
public:
	Pioneer( const Coord& pos, const std::vector< Coord >& root );
	virtual ~Pioneer( );
private:
	void action( );
	bool _is_attack;
	Coord _pop_point;
};

