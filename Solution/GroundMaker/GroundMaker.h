#pragma once
#include "Ground.h"
#include <string>

PTR( GroundMaker );

class GroundMaker : public Ground {
public:
	GroundMaker( );
	virtual ~GroundMaker( );
private:
	void loadToCSV( );
	void save( );
private:
	std::string _file_name;
};

