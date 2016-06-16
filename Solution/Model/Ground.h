#pragma once

#include "smart_ptr.h"
#include <vector>

PTR( Ground );
PTR( Binary )p;

class Ground {
public:
	enum TYPE {
		TYPE_PLAIN   ,
		TYPE_DESERT	 ,
		TYPE_MOUNTAIN,
		TYPE_RIVER	 ,
		MAX_TYPE
	};
public:
	Ground( BinaryPtr binary );
	Ground( int width, int height );
	virtual ~Ground( );
public:
	void setType( int mx, int my, TYPE type );
	void setType( int idx, TYPE type );
	TYPE getType( int mx, int my ) const;
	TYPE getType( int idx ) const;
	int getWidth( ) const;
	int getHeight( ) const;
	void load( );
private:
	int getIdx( int mx, int my ) const;
	void init( );
private:
	TYPE* _array_type;
	int _width;
	int _height;
};