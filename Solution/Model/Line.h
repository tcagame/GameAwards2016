#pragma once
#include "Coord.h"
#include "Ratio.h"
#include "Chip.h"
#include "smart_ptr.h"
#include <array>
#include <vector>

PTR( Line );
PTR( Map );
PTR( Facility );
PTR( Powerplant );
PTR( Chargers );
PTR( Bases );
PTR( Refineries );
PTR( Bulletins );
PTR( Packet );


class Line {
public:
	enum STATE {
		STATE_NONE,
		STATE_CONNECT,
		STATE_CIRCUIT,
		STATE_MAX,
	};

	struct Chip {
		bool is_check;
		bool guide;
		unsigned char form_dir; //dir
		unsigned char circuit_dir; //dir
	};
	
	static const int PACKET_NUM = 10;

	static const unsigned char DIR_NONE	= 0x00;
	static const unsigned char DIR_U___ = 0x01;
	static const unsigned char DIR__D__ = 0x02;
	static const unsigned char DIR___L_ = 0x04;
	static const unsigned char DIR____R = 0x08;
	static const unsigned char DIR___LR = DIR___L_ + DIR____R;
	static const unsigned char DIR_UD__ = DIR_U___ + DIR__D__;
	static const unsigned char DIR_U__R = DIR_U___ + DIR____R;
	static const unsigned char DIR_U_L_ = DIR_U___ + DIR___L_;
	static const unsigned char DIR__D_R = DIR__D__ + DIR____R;
	static const unsigned char DIR__DL_ = DIR__D__ + DIR___L_;
	static const unsigned char DIR_U_LR = DIR_U___ + DIR___L_ + DIR____R;
	static const unsigned char DIR__DLR = DIR__D__ + DIR___L_ + DIR____R;
	static const unsigned char DIR_UD_R = DIR_U___ + DIR__D__ + DIR____R;
	static const unsigned char DIR_UDL_ = DIR_U___ + DIR__D__ + DIR___L_;
	static const unsigned char DIR_UDLR = DIR_U___ + DIR__D__ + DIR___L_ + DIR____R;

public:
	Line( MapPtr map, PowerplantPtr powerplant, ChargersPtr chargers, BasesPtr bases, RefineriesPtr refineries, BulletinsPtr bulletins );
	virtual ~Line( );
public:
	void update( );
	void makeCircuit( );
	const Chip& getChip( const Coord& coord ) const;
	bool isGuiding( ) const;
	void startGuide( const Coord& coord );
	void setGuide( const Coord& coord );
	void endGuide( const Coord& coord );
	void cancelGuide( );
	bool setDeleteGuide( const Coord& coord );
	void deleteAlongGuide( const Coord& coord );
	unsigned char getNextDir( const Coord& coord ) const;
	PacketPtr getPacket( int idx ) const;
	bool setGuideAlongMouse( const Coord& coord );
private:
	FacilityConstPtr getChipType( CHIP_TYPE chip_type, unsigned char value );
	bool checkDelete( const Coord& coord, const Coord& old_coord );
	bool makeCircuitNext( const Coord& coord, const Coord& old_coord );
	bool setConnectNew( const Coord& coord, const Coord& old_coord );
	bool setDeleteNew( const Coord& coord, const Coord& old_coord );
	void setConnectNext( const Coord& coord, unsigned char next_dir );
	void setDeleteNext( const Coord& coord, unsigned char next_dir );
	void initGuideArray( );
	bool checkDeleteDir ( const Coord& coord, unsigned char next_dir );
	unsigned char getNowDir( const Coord& coord, const Coord& old_coord );
	unsigned char reverseDir( unsigned char dir ) const;
	bool setConnectFacility( const Coord& coord );
	bool destroyLineDir( CHIP_TYPE type, const Coord& coord );
	void outputPackets( );
	void updatePackets( );
	bool isGuidingLength( const Coord& coord );

private:
	MapPtr _map;
	PowerplantPtr _powerplant;
	ChargersPtr _chargers;
	BasesPtr _bases;
	RefineriesPtr _refineries;
	BulletinsPtr _bulletins;
	std::array< Chip, COORD_WIDTH * COORD_HEIGHT > _chips;
	Coord _old_coord;
	bool _guide_mode;
	bool _circuit;
	unsigned char _guide_store_from_dir;
	unsigned char _guide_store_circuit_dir;
	STATE _guide_store_state;
	Coord _guide_start_coord;
	Coord _line_start_coord;
	Coord _delete_coord_first_conecter;
	Coord _delete_coord_second_conecter;
	Coord _guide_line_coord;

	std::array< PacketPtr, PACKET_NUM > _packets;
	unsigned int _packets_count;
};
