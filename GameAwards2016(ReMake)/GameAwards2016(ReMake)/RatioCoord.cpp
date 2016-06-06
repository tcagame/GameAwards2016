#include "RatioCoord.h"

RatioCoord::RatioCoord( const Coord& pos ) {
	_coord = pos;
}

RatioCoord::~RatioCoord( ) {
}

void RatioCoord::increase( const Coord& vec ) {
	const int RATIO_MAX = _ratio.x.RATIO_ACCURACY;
	if ( ( int )_ratio.x.value + vec.x >= RATIO_MAX ) {
		_coord.x += 1;
	}
	if ( ( int )_ratio.y.value + vec.y >= RATIO_MAX ) {
		_coord.y += 1;
	}
	if ( ( int )_ratio.x.value + vec.x < 0 ) {
		_coord.x -= 1;
	}
	if ( ( int )_ratio.y.value + vec.y < 0 ) {
		_coord.y -= 1;
	}
	_ratio.x.increase( ( int )vec.x );
	_ratio.y.increase( ( int )vec.y );
}

Coord RatioCoord::getCoord( ) const {
	return _coord;
}

RatioCoord::RatioPoint RatioCoord::getRatio( ) const {
	return _ratio;
}

Vector RatioCoord::getCoordWithRatio( ) const {
	Vector result;
	const int RATIO_MAX = _ratio.x.RATIO_ACCURACY;
	result.x = _coord.x * RATIO_MAX + _ratio.x.value;
	result.x /= RATIO_MAX;
	result.y = _coord.y * RATIO_MAX + _ratio.y.value;
	result.y /= RATIO_MAX;
	return result;
}