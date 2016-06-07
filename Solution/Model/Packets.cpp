#include "Packets.h"
#include "Packet.h"
#include "Line.h"


Packets::Packets( LineConstPtr line ) :
_packet_num( 0 ),
_line( line ) {
	
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
	const Line::Data& data = _line->getData( );
	unsigned char dir = data.array[ coord.getIdx( ) ].circuit_dir;
	unsigned char from_dir = data.array[ coord.getIdx( ) ].form_dir;
	_packets[ _packet_num ] = PacketPtr( new Packet( coord, Ratio( Ratio::RATIO_ACCURACY ), Ratio( Ratio::RATIO_ACCURACY / 2 ) ) );
	_packets[ _packet_num ]->setDir( dir, from_dir );
	_packet_num++;
}

void Packets::update( ) {
	const Line::Data& data = _line->getData( );
	for ( int i = 0; i < _packet_num; i++ ) {
		_packets[ i ]->update( );
		unsigned char packet_dir = _packets[ i ]->getNextDir( );	
		int idx = _packets[ i ]->getCoord( ).getIdx( );
		unsigned char dir = data.array[ idx ].circuit_dir;
		if ( !_packets[ i ]->isMoveNextCoord( ) && packet_dir == dir ) {
			continue;
		}
		unsigned char from_dir = data.array[ idx ].form_dir;
		_packets[ i ]->setDir( dir, from_dir );
		
	}
}
