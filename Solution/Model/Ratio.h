#pragma once

struct Ratio {
	unsigned int value;
	static const unsigned int ACCURACY = 1000;

	Ratio( ) : value( 0 ) { }
	Ratio( int value_ ) : value( value_ ) { }
	Ratio( int value_, int max_ ) : value( value_* ACCURACY / max_ ) { }
	void increase( unsigned int n ) {
		value += n;
	}
	int cal( int n ) const {
		return n * value / ACCURACY;
	}
	bool isOverflow( ) const {
		return value >= ACCURACY;
	}
	void reflesh( ) {
		value %= ACCURACY;
	}

	bool isPassedHalf( ) const {
		return value >= ACCURACY / 2;
	}
};

