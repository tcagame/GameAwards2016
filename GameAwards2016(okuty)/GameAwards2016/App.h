#pragma once

#include "Task.h"
#include "Coord.h"
#include <string>

PTR( App );
PTR( Map );
PTR( Line );
PTR( Powerplant );
PTR( Chargers );
PTR( Bases );
PTR( Refineries );
PTR( Bulletins );

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
	PowerplantConstPtr getPowerplant( ) const;
	ChargersConstPtr getChargers( ) const;
	LineConstPtr getLine( ) const;
	BasesConstPtr getBases( ) const;
	RefineriesConstPtr getRefineries( ) const;
	BulletinsConstPtr getBulletins( ) const;
	bool isModeDeleteLine( ) const;
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
	LinePtr _line;
	PowerplantPtr _powerplant;
	ChargersPtr _chargers;
	BasesPtr _bases;
	RefineriesPtr _refineries;
	BulletinsPtr _bulletins;
	MODE _mode;
	Coord _click_push_coord;
	FACILITY _placement_facility;
	bool _operating_relocation;
	unsigned char _relocation_idx;
	Coord _before_coord;
};