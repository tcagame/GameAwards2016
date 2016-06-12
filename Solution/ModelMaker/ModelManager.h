#pragma once
#include "Framework.h"
#include "smart_ptr.h"

PTR( ModelManager );
PTR( MapMaker );
PTR( FileManager );
PTR( Model );

class ModelManager {
public:
	ModelManager();
	ModelManager( MapMakerPtr map_maker, FileManagerPtr file_manager, ModelPtr model );
	virtual ~ModelManager();
public:
	void loadModel( );
private:
	void loadMountainModel( int mx, int my );
	void loadPlainModel( int mx, int my );
	void loadDesertModel( int mx, int my );
	void loadRiverModel( int mx, int my );
	void setDrawModel( );
	std::string getModelFile( int idx, unsigned char type );

private:
	MapMakerPtr _map_maker;
	FileManagerPtr _file_manager;
	ModelPtr _model;
};

