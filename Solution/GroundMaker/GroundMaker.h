#pragma once
#include "Ground.h"
#include "Task.h"
#include "GroundChip.h"
#include "MapChip.h"
#include <string>

PTR( GroundMaker );
PTR( ModelMake );
PTR( Viewer );

enum STATE {
	STATE_INPUT,
	STATE_LOAD,
	STATE_MAKE,
	STATE_SAVE,
	STATE_END,
	STATE_MAX,
};

class GroundMaker : public Ground, public Task {
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
	void mapMake( );
	void mdlMake( );
	void save( );

	void makeMountain( int mx, int my );
	void makeRiver( int mx, int my );
	void makePlane( int mx, int my );
	void makeDesert( int mx, int my );
private:
	std::string _file_name;
	STATE _state;
	ModelMakePtr _model_make;
	ViewerPtr _viewer;

	int _map_width;
	int _map_height;
	std::vector< MAP_TYPE > _plane_map;
	std::vector< MAP_TYPE > _desert_map;
	std::vector< MAP_TYPE > _mountain_map;
	std::vector< MAP_TYPE > _river_map;
};

