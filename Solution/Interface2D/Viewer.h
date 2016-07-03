#pragma once
#include "Line.h"
#include "Task.h"
#include "Coord.h"
#include <string>
#include <array>

PTR( Viewer );

class Viewer : public Task {
public:
	enum VIEWER_LINE_VALUE {
		VIEWER_LINE_VALUE___LR,
		VIEWER_LINE_VALUE_UD__,
		VIEWER_LINE_VALUE_U__R,
		VIEWER_LINE_VALUE_U_L_,
		VIEWER_LINE_VALUE__D_R,
		VIEWER_LINE_VALUE__DL_,
		VIEWER_LINE_VALUE_U_LR,
		VIEWER_LINE_VALUE__DLR,
		VIEWER_LINE_VALUE_UD_R,
		VIEWER_LINE_VALUE_UDL_,
		VIEWER_LINE_VALUE_UDLR,
		VIEWER_LINE_VALUE_ARROW_R,
		VIEWER_LINE_VALUE_ARROW_L,
		VIEWER_LINE_VALUE_NONE,
	};

	enum CLICK {
		CLICK_NONE,
		CLICK_PUSH,
		CLICK_HOLD,
		CLICK_RELEASE,
		MAX_CLICK
	};

	enum GUIDE {
		GUIDE_NONE,
		GUIDE_CHARGER,
		GUIDE_BASE,
		GUIDE_REFINERY,
		GUIDE_BULLETIN,
		MAX_GUIDE
	};

public:
	static ViewerPtr getTask( );
	static std::string getTag( ) { return "VIEWER"; }
public:
	Viewer();
	virtual ~Viewer();
public:
	void initialize( );
	void update( );
	void setGuidFacility( const Coord& coord, GUIDE guide );
	Coord getClickCoord( ) const;
	CLICK getClickLeft( ) const;
	CLICK getClickRight( ) const;
private:
	void updateClick( );
	void drawGround( ) const;
	void drawPowerplant( ) const;
	void drawChargers( ) const;
	void drawBases( ) const;
	void drawRefineries( ) const;
	void drawBulletins( ) const;
	void drawGuidFacility( ) const;
	void drawGuideLine( ) const;
	void drawLine( ) const;
	void drawPacket( ) const;
	void drawGoldMines( ) const;
	void drawForests( ) const;
	void drawEnemies( ) const;
	void drawGuadians( ) const;
	void drawMiners( ) const;
	void drawPioneers( ) const;
	void drawBear( ) const;
	void drawBee( ) const;
	unsigned char reverseDir( unsigned char start_dir ) const;
	int convLineTypeToIdx( unsigned char dir ) const;
	void reflesh( );
	void setPacketAnimation( int& sx, int& sy, unsigned char dir_in, unsigned char dir_out, Ratio ratio ) const;
private:

	Coord _click_coord;
	CLICK _click_left;
	CLICK _click_right;
	Coord _coord_guid;
	GUIDE _guide;
	int _count;
};

