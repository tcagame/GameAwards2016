#pragma once

#include "Task.h"
#include "GroundChip.h"
#include "MapChip.h"
#include <string>
#include <vector>

PTR( GroundMaker );
PTR( Model );
PTR( Ground );


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
	bool makeGround( );
	bool makeModel( );
	std::string getModelFile( int idx, unsigned char type );
	unsigned char makeModelChip( int mx, int my, GROUND_CHIP_TYPE type );
private:
	std::string _file_name;
	GroundPtr _ground;
};

