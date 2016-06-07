#include "Packet.h"
#include "Coord.h"
#include "Ratio.h"
#include "Line.h"
#include <assert.h>

const int POWERPLANT_LEVEL = Ratio::ACCURACY * 10 / 100; // 10Åì

Packet::Packet( ) {
	_waiting = true;
}


Packet::~Packet( ) {
}

Coord Packet::getCoord( ) {
	return _coord;
}

Ratio Packet::getAnimationRatio( ) const {
	return _animation_ratio;
}


void Packet::update( ) {
	if ( _waiting ) {
		return;
	}

	// êiÇﬂÇÈ
	_animation_ratio.increase( POWERPLANT_LEVEL );
}

bool Packet::isWaiting( ) const {
	return _waiting;
}

bool Packet::isFinishedAnimation( ) const {
	return _animation_ratio.isOverflow( );
}

void Packet::nextChip( unsigned char dir ) {
	switch( dir ) {
	case Line::DIR_U___:
		_coord.y--;
		break;
	case Line::DIR__D__:
		_coord.y++;
		break;
	case Line::DIR___L_:
		_coord.x--;
		break;
	case Line::DIR____R:
		_coord.x++;
		break;
	default:
		assert( false );
	}

	_animation_ratio.reflesh( );
}

void Packet::set( const Coord& coord ) {
	_waiting = false;
	_coord = coord;
}

void Packet::wait( ) {
	_waiting = true;
}