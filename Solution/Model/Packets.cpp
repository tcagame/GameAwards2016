#include "Packets.h"
#include "Packet.h"


Packets::Packets( ) :
_packet_num( 0 ) {
	
}


Packets::~Packets( ) {

}

PacketPtr Packets::get( int idx ) const {
	return _packets[ idx ];
}

int Packets::getCount( ) const {
	return _packet_num;
}

void Packets::creatPacket( Coord& coord ) {
	if ( _packet_num >= PACKET_NUM ) {
		return;
	}
	_packets[ _packet_num ] = PacketPtr( new Packet( coord ) );
	_packet_num++;
}

void Packets::update( ) {
	for ( int i = 0; i < _packet_num; i++ ) {
		_packets[ i ]->update( );
	}
}
