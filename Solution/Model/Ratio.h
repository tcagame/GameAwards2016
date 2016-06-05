#pragma once

struct Ratio {
	unsigned int value = 0;
	static const unsigned int RATIO_ACCURACY = 1000;
	bool increase( int n ) {
		bool ret = false;
		if ( value + n >= RATIO_ACCURACY ) {
			ret = true;
		}
		value = ( value + n ) % RATIO_ACCURACY;
		return ret;
	}
	int cal( int n ) const {
		return n * value / RATIO_ACCURACY;
	}
};

