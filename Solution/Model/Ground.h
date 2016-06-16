#pragma once

#include "smart_ptr.h"
#include <vector>

PTR( Ground );
PTR( Binary );

#include "GroundChip.h"

class Ground {
public:
	Ground( BinaryPtr binary );
	Ground( int width, int height );
	virtual ~Ground( );
public:
	void setType( int mx, int my, GROUND_CHIP_TYPE type );
	GROUND_CHIP_TYPE getType( int mx, int my ) const;
	int getWidth( ) const;
	int getHeight( ) const;
	BinaryPtr makeBinary( );
private:
	int getIdx( int mx, int my ) const;
	void init( );
private:
	GROUND_CHIP_TYPE* _array_type;
	int _width;
	int _height;
};