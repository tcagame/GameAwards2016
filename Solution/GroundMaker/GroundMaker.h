#pragma once
#include "Ground.h"
#include <string>

class GroundMaker : public Ground {
public:
	GroundMaker( );
	virtual ~GroundMaker( );
private:
	void load( );
	void save( );
private:
	std::string _file_name;
};

