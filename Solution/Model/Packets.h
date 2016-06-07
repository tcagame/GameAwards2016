#pragma once

#include "smart_ptr.h"
#include "Coord.h"
#include <array>

PTR( Packets );
PTR( Packet );
PTR( Line );

class Packets {
public:
	Packets( LineConstPtr line );
	virtual ~Packets( );
public:
	void creatPacket( Coord& coord );
	PacketPtr get( int idx ) const;
	int getCount( ) const;
	void update( );
private:
	static const int PACKET_NUM = 10;
private:
	std::array< PacketPtr, PACKET_NUM > _packets;
	int _packet_num;
	LineConstPtr _line;
};

