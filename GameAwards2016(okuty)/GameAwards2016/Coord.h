#pragma once

const int COORD_WIDTH  = 64;
const int COORD_HEIGHT = 48;

struct Coord {
	int x;
	int y;

	Coord( ) :
		x( 0 ),
		y( 0 ) { 

	}

	Coord( int x_, int y_ ) : x( x_ ), y( y_ ) { }

	int getIdx( ) const {
		if ( x < 0 || y < 0 || x >= COORD_WIDTH || y >= COORD_HEIGHT ) {
			return -1;
		} 
		return x + y * COORD_WIDTH;
	}
};
