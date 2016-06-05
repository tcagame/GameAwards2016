#include "Packet.h"
#include "Coord.h"
#include "Ratio.h"


Packet::Packet( const Coord& coord ) :
_coord( coord ) {
}


Packet::~Packet( ) {
}

Coord Packet::getCoord( ) {
	return _coord;
}
Ratio Packet::getRatioX( ) {
	return Ratio( );
}


Ratio Packet::getRatioY( ) {
	return Ratio( );
}
void Packet::update( ) {
	_coord.x++;
}