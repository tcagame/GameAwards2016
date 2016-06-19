#pragma once

#include "Task.h"
#include "GroundChip.h"
#include "MapChip.h"
#include <string>
#include <vector>

PTR( GroundMaker );
PTR( ModelMake );
PTR( Viewer );
PTR( Ground );

enum STATE {
	STATE_INPUT,
	STATE_LOAD,
	STATE_MAKE,
	STATE_SAVE,
	STATE_VIEWER,
	STATE_MAX,
};

class GroundMaker : public Task {
public:
	static GroundMakerPtr getTask( );
	static std::string getTag( ) { return "GROUND_MAKER"; }
public:
	GroundMaker( );
	virtual ~GroundMaker( );
public:
	void update( );
	MAP_TYPE getMapType( int mx, int my, GROUND_CHIP_TYPE type );
	int getMapWidth( );
	int getMapHeight( );
private:
	bool inputFileName( );
	void loadToCSV( );
	void makeGroundModel( );
	void mdlMake( );
	void save( );
	unsigned char makeModelChip( int mx, int my, GROUND_CHIP_TYPE type );
	void viewer( );
private:
	std::string _file_name;
	STATE _state;
	ModelMakePtr _model_make;
	ViewerPtr _viewer;
	GroundPtr _ground;
	std::vector< unsigned char > _plain_map;
	std::vector< unsigned char > _desert_map;
	std::vector< unsigned char > _mountain_map;
	std::vector< unsigned char > _river_map;
};

