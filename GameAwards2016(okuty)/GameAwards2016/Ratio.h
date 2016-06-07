#pragma once

struct Ratio {
	unsigned int value = 0;
	const unsigned int RATIO_ACCURACY = 1000;
	void increase( int n ) {
		if ( ( int )value + n < 0 ) {
			value = RATIO_ACCURACY + ( ( int )value + n );
		} else {
			value = ( value + n ) % RATIO_ACCURACY;
		}
	}
	int cal( int n ) const {
		return n * value / RATIO_ACCURACY;
	}
};

