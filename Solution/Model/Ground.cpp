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

GROUND_CHIP_TYPE Ground::getTypeTerrain( int mx, int my ) const {
	if ( mx < 0 || mx >= _width ||
		 my < 0 || my >= _height ) {
			return GROUND_CHIP_TYPE_RIVER;
	}
	GROUND_CHIP_TYPE chip = _array_type[ getIdx( mx, my ) ];
	if ( chip == GROUND_CHIP_TYPE_TREE ) {
		chip = GROUND_CHIP_TYPE_DESERT;
	}
	if ( chip == GROUND_CHIP_TYPE_FLOWER ) {
		chip = GROUND_CHIP_TYPE_PLAIN;
	}
	if ( chip == GROUND_CHIP_TYPE_BEAR ) {
		chip = GROUND_CHIP_TYPE_PLAIN;
	}
	if ( chip == GROUND_CHIP_TYPE_BEE ) {
		chip = GROUND_CHIP_TYPE_PLAIN;
	}
	if ( chip == GROUND_CHIP_TYPE_POWERPLANT ) {
		chip = GROUND_CHIP_TYPE_DESERT;
	}

	return chip;
}

GROUND_CHIP_TYPE Ground::getType( int mx, int my ) const {
	if ( mx < 0 || mx >= _width ||
		 my < 0 || my >= _height ) {
			return GROUND_CHIP_TYPE_RIVER;
	}
	GROUND_CHIP_TYPE chip = _array_type[ getIdx( mx, my ) ];

	return chip;
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

	binary->ensure( sizeof( GROUND_CHIP_TYPE ) * _width * _height + sizeof( unsigned int ) * 2 );
	binary->write( &_width, sizeof( unsigned int ) );
	binary->write( &_height, sizeof( unsigned int ) );
	binary->write( _array_type, sizeof( GROUND_CHIP_TYPE ) * _width * _height );

	return binary;
}

void Ground::toThinningTrees( ) {
	for ( int i = 0; i < _width; i++ ) {
		for ( int j = 0; j < _height; j++ ) {
			GROUND_CHIP_TYPE chip = getType( i, j );
			if ( chip != GROUND_CHIP_TYPE_TREE ) {
				continue;
			}
			// ŽüˆÍ‚É–Ø‚ª‚ ‚Á‚½‚çíœ
			for ( int k = 0; k < 5 * 5; k++ ) {
				int mx = i - 2 + k % 5;
				int my = j - 2 + k / 5;
				if ( mx == i && my == j ) {
					continue;
				}
				GROUND_CHIP_TYPE target = getType( mx, my );
				if ( target == GROUND_CHIP_TYPE_TREE ) {
					setType( mx, my, GROUND_CHIP_TYPE_PLAIN );
				}
			}
		}
	}
}
void Ground::toFlatFlower( ) {
	for ( int i = 0; i < _width; i++ ) {
		for ( int j = 0; j < _height; j++ ) {
			GROUND_CHIP_TYPE chip = getType( i, j );
			if ( chip != GROUND_CHIP_TYPE_FLOWER ) {
				continue;
			}
			//”ÍˆÍ“à‚ð•½’n‚É‚·‚é
			for ( int k = 0; k < 3 * 3; k++ ) {
				int mx = i + k % 3;
				int my = j + k / 3;
				if ( mx == i && my == j ) {
					continue;
				}
				GROUND_CHIP_TYPE target = getType( mx, my );
				setType( mx, my, GROUND_CHIP_TYPE_PLAIN );
			}
		}
	}
}

void Ground::toFlatPowerPlant( ) {
	for ( int i = 0; i < _width; i++ ) {
		for ( int j = 0; j < _height; j++ ) {
			GROUND_CHIP_TYPE chip = getType( i, j );
			if ( chip != GROUND_CHIP_TYPE_POWERPLANT ) {
				continue;
			}
			//”ÍˆÍ“à‚ðr’n‚É‚·‚é
			for ( int k = 0; k < 5 * 5; k++ ) {
				int mx = i + k % 5;
				int my = j + k / 5;
				if ( mx == i && my == j ) {
					continue;
				}
				GROUND_CHIP_TYPE target = getType( mx, my );
				setType( mx, my, GROUND_CHIP_TYPE_DESERT );
			}
		}
	}
}



