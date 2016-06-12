#pragma once
#include "Task.h"
#include <string>

PTR( Viewer );
PTR( MapMaker );

class Viewer : public Task {
public:
	static ViewerPtr getTask( );
	static std::string getTag( ) { return "VIEWER"; }
public:
	Viewer( MapMakerPtr map_maker );
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
private:
	MapMakerPtr _map_maker;
};

