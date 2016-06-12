#pragma once
#include "Task.h"
#include <string>

PTR( Viewer );
PTR( MapMaker );
PTR( FileManager );
PTR( Model );

class Viewer : public Task {
public:
	static ViewerPtr getTask( );
	static std::string getTag( ) { return "VIEWER"; }
public:
	Viewer( MapMakerPtr map_maker, FileManagerPtr file_manager, ModelPtr model );
	virtual ~Viewer();
public:
	void initialize( );
	void update( );
private:
	void drawMap( ) const;
	void drawPlain( int mx, int my ) const;
	void drawDesert( int mx, int my ) const;
	void drawMountain( int mx, int my ) const;
	void drawRiver( int mx, int my ) const;
	void setDrawModel( );
private:
	MapMakerPtr _map_maker;
	FileManagerPtr _file_manager;
	ModelPtr _model;
};

