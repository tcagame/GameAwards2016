#include "Packet.h"
#include "Coord.h"
#include "Line.h"
#include <assert.h>

Packet::Packet( ) {
	_waiting = true;
}


Packet::~Packet( ) {
}

Coord Packet::getCoord( ) {
	return _coord;
}

bool Packet::isWaiting( ) const {
	return _waiting;
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
}

void Packet::set( const Coord& coord ) {
	_waiting = false;
	_coord = coord;
}

void Packet::wait( ) {
	_waiting = true;
}