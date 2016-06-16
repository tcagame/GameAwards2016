#include "Ground.h"
#include "Binary.h"
#include <assert.h>

Ground::Ground( int width, int height ) :
_array_type( NULL ),
_width ( width ),
_height( height ) {
	_array_type = new TYPE[ _width * _height ];
}

Ground::Ground( BinaryPtr binary ) :
_array_type( NULL ),
_width ( 0 ),
_height( 0 ) {
	binary->seek( );
	binary->read( &_width , sizeof( _width  ) );
	binary->read( &_height, sizeof( _height ) );

	_array_type = new TYPE[ _width * _height ];

	binary->read( _array_type, sizeof( TYPE ) * _width * _height );
}

Ground::~Ground( ) {
	delete [ ] _array_type;
}

Ground::TYPE Ground::getType( int mx, int my ) const {
	return getType( getIdx( mx, my ) );
}

Ground::TYPE Ground::getType( int idx ) const {
	assert( _array_type );

	return _array_type[ idx ];
}

int Ground::getWidth( ) const {
	return _width;
}

int Ground::getHeight( ) const {
	return _height;
}


void Ground::setType( int idx, TYPE type ) {
	assert( _array_type );

	_array_type[ idx ] = type;
}

void Ground::setType( int mx, int my, TYPE type ) {
	setType( getIdx( mx, my ), type );
}

int Ground::getIdx( int mx, int my ) const {
	assert( mx >= 0 );
	assert( my >= 0 );
	assert( mx < _width );
	assert( my < _height );

	return mx + my * _width;
}
