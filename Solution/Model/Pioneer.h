#pragma once
#include "Character.h"
#include "smart_ptr.h"
#include <vector>

PTR( Pioneer );
PTR( Forest );

class Pioneer : public Character {
public:
	Pioneer( const std::vector< Coord >& root, ForestPtr forest );
	virtual ~Pioneer( );
private:
	void action( );
	bool existMaterial( );
private:
	bool _is_attack;
	Coord _pop_point;
	ForestPtr _forest;
};

