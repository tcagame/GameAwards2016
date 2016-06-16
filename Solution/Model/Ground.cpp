#include "Ground.h"
#include "Binary.h"
#include <assert.h>

Ground::Ground( int width, int height ) :
_array_type( NULL ),
_width ( width ),
_height( height ) {
	_array_type = new GROUND_CHIP_TYPE[ _width * _height ];
}

Ground::Ground( BinaryPtr binary ) :
_array_type( NULL ),
_width ( 0 ),
_height( 0 ) {
	binary->seek( );
	binary->read( &_width , sizeof( _width  ) );
	binary->read( &_height, sizeof( _height ) );

	_array_type = new GROUND_CHIP_TYPE[ _width * _height ];

	binary->read( _array_type, sizeof( GROUND_CHIP_TYPE ) * _width * _height );
}

Ground::~Ground( ) {
	delete [ ] _array_type;
}

GROUND_CHIP_TYPE Ground::getType( int mx, int my ) const {
	if ( mx < 0 || mx >= _width ||
		 my < 0 || my >= _height ) {
			return GROUND_CHIP_TYPE_RIVER;
	}
	return _array_type[ getIdx( mx, my ) ];
}

int Ground::getWidth( ) const {
	return _width;
}

int Ground::getHeight( ) const {
	return _height;
}

void Ground::setType( int mx, int my, GROUND_CHIP_TYPE type ) {
	if ( mx < 0 || mx >= _width ||
		 my < 0 || my >= _height ) {
			return;
	}
	_array_type[ getIdx( mx, my ) ] = type;
}

int Ground::getIdx( int mx, int my ) const {
	return mx + my * _width;
}

BinaryPtr Ground::makeBinary( ) {
	BinaryPtr binary( new Binary );

	binary->write( &_width, sizeof( unsigned int ) );
	binary->write( &_height, sizeof( unsigned int ) );
	binary->write( _array_type, sizeof( GROUND_CHIP_TYPE ) * _width * _height );

	return binary;
}

