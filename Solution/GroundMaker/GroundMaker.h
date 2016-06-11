#pragma once
#include "Ground.h"
#include <string>

PTR( GroundMaker );

class GroundMaker : public Ground {
public:
	GroundMaker( );
	virtual ~GroundMaker( );
	void loadToCSV( std::string file_name );
	void save( );
};

