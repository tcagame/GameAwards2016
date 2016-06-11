#pragma once
#include "GroundChip.h"
#include "smart_ptr.h"
#include <vector>

PTR( Ground );

class Ground {
public:
	Ground( );
	virtual ~Ground( );
public:
	GROUND_CHIP_TYPE getGroundChip( int idx ) const;
	int getWidth( ) const;
	int getHeight( ) const;
	void load( );
protected:
	std::vector< GROUND_CHIP_TYPE > _data;
	int _width;
	int _height;
};