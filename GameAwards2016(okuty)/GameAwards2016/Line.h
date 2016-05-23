#pragma once
#include "Coord.h"
#include "Chip.h"
#include "smart_ptr.h"
#include <array>

PTR( Line );
PTR( Map );
PTR( Facility );
PTR( Powerplant );
PTR( Chargers );
PTR( Bases );
PTR( Refineries );
PTR( Bulletins );


class Line {
public:
	enum STATE {
		STATE_NONE,
		STATE_NORMAL,
		STATE_GUIDE,
		STATE_CIRCUIT,
		STATE_DELETE,
		STATE_MAX,
	};
	struct Data {
		struct Chip {
			STATE state;
			bool is_check;
			unsigned char type; //dir
		};
		std::array< Chip, COORD_WIDTH * COORD_HEIGHT > array;
	};

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
	void reflesh( );
	const Data& getData( ) const;
	bool isGuiding( ) const;
	void startGuide( const Coord& coord );
	void setGuide( const Coord& coord );
	void endGuide( const Coord& coord );
	void cancelGuide( );
	void deleteLine( const Coord& coord );
private:
	FacilityConstPtr getChipType( CHIP_TYPE chip_type, unsigned char value );
	bool checkDelete( const Coord& coord, const Coord& old_coord );
	void destroyLine( );
	bool makeCircuit( const Coord& coord, const Coord& old_coord );
	bool setConnectNew( const Coord& coord, const Coord& old_coord, STATE state );
	void setConnectNext( const Coord& coord, unsigned char next_dir, STATE state );				//( const Coord& coord, const Coord& in_coord, unsigned char check, int dx, int dy );
	void initGuideArray( );
	bool checkConnectDir ( const Coord& coord, unsigned char next_dir );
	bool checkDeleteDir ( const Coord& coord, unsigned char next_dir );
	unsigned char getNowDir( const Coord& coord, const Coord& old_coord );
	unsigned char reverseDir( unsigned char dir ) const;
	bool setConnectFacility( const Coord& coord );
	Coord getFacilityConnectCoord( const Coord& coord );
	bool destroyLineDir( CHIP_TYPE type, const Coord& coord );

private:
	MapPtr _map;
	PowerplantPtr _powerplant;
	ChargersPtr _chargers;
	BasesPtr _bases;
	RefineriesPtr _refineries;
	BulletinsPtr _bulletins;
	Data _data;
	Coord _old_coord;
	bool _guide_mode;
	unsigned char _guide_store_dir;
	STATE _guide_store_state;
	Coord _guide_start_coord;
	Coord _line_start_coord;
	bool _is_delete;
	Coord _delete_coord_first_conecter;
	Coord _delete_coord_second_conecter;

};
