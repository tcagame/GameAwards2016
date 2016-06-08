#pragma once

#include "Task.h"
#include "Coord.h"
#include <string>

PTR( App );
PTR( Map );
PTR( UnitMap );
PTR( Line );
PTR( Powerplant );
PTR( Chargers );
PTR( Bases );
PTR( Refineries );
PTR( Bulletins );
PTR( Packets );
PTR( GoldMines );
PTR( Forests );
PTR( Miners );
PTR( Pioneers );

class App : public Task {
public:
	static AppPtr getTask( );
	static std::string getTag( ) { return "APP"; }
public:
	App( );
	virtual ~App( );
public:
	void update( );
	MapConstPtr getMap( ) const;
	MapPtr getMap( );
	UnitMapConstPtr getUnitMap( ) const;
	UnitMapPtr getUnitMap( );
	PowerplantConstPtr getPowerplant( ) const;
	ChargersConstPtr getChargers( ) const;
	LineConstPtr getLine( ) const;
	BasesConstPtr getBases( ) const;
	RefineriesConstPtr getRefineries( ) const;
	BulletinsConstPtr getBulletins( ) const;
	PacketsConstPtr getPackets( ) const ;
	GoldMinesPtr getGoldMines( );
	MinersConstPtr getMiners( ) const;
	MinersPtr getMiners( );
	PioneersConstPtr getPioneers( ) const;
	ForestsPtr getForests( );
	bool isModeDeleteLine( ) const;
	
	//void addGold( int gold );
private:
	enum MODE {
		MODE_LINE,
		MODE_DELETE_LINE,
		MODE_PLACEMENT,
		MAX_MODE
	};
	enum FACILITY {
		FACILITY_BASE,
		FACILITY_BULLETIN,
		FACILITY_CHARGER,
		FACILITY_REFINERY,
		FACILITY_POWERPLANT,
		MAX_FACILITY
	};
private:
	void doChangePlacementOperation( );
	void doPlacementOperation( );
	void doFacilityPlacementOperation( );
	void doLinePlacementOperation( );
	void doLineDeleteOperation( );
	void doFacilityMoveOperation( );
private:
	MapPtr _map;
	UnitMapPtr _unit_map;
	LinePtr _line;
	PowerplantPtr _powerplant;
	ChargersPtr _chargers;
	BasesPtr _bases;
	RefineriesPtr _refineries;
	BulletinsPtr _bulletins;
	GoldMinesPtr _gold_mines;
	ForestsPtr _forests;
	MinersPtr _miners;
	PioneersPtr _pioneers;
	MODE _mode;
	Coord _click_push_coord;
	FACILITY _placement_facility;
	PacketsPtr _packets;
	bool _operating_relocation;
	unsigned char _relocation_idx;
	Coord _before_coord;
	
	//int _gold;
};