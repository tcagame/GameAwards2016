#pragma once

#include "smart_ptr.h"
#include <string>

PTR( Parser );
PTR( Model );

class Parser {
public:
	Parser();
	virtual ~Parser();
public:
	bool load( std::string filename );
	ModelPtr makeModel( );
};

