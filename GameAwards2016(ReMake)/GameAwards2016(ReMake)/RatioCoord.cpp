#include "RatioCoord.h"

RatioCoord::RatioCoord( const Coord& pos ) {
	_pos = pos;
}

RatioCoord::~RatioCoord( ) {
}

void RatioCoord::increase( const Coord& vec ) {
	const int RATIO_MAX = _ratio.x.RATIO_ACCURACY;
	if ( ( int )_ratio.x.value + vec.x >= RATIO_MAX ) {
		_pos.x += 1;
	}
	if ( ( int )_ratio.y.value + vec.y >= RATIO_MAX ) {
		_pos.y += 1;
	}
	if ( ( int )_ratio.x.value + vec.x < 0 ) {
		_pos.x -= 1;
	}
	if ( ( int )_ratio.y.value + vec.y < 0 ) {
		_pos.y -= 1;
	}
	_ratio.x.increase( ( int )vec.x );
	_ratio.y.increase( ( int )vec.y );
}

Coord RatioCoord::getPos( ) const {
	return _pos;
}

RatioCoord::RatioPoint RatioCoord::getRatio( ) const {
	return _ratio;
}

Vector RatioCoord::getCoordWithRatio( ) const {
	Vector result;
	result.x = _pos.x + _ratio.x.value / _ratio.x.RATIO_ACCURACY;
	result.y = _pos.y + _ratio.y.value / _ratio.y.RATIO_ACCURACY;
	return result;
}