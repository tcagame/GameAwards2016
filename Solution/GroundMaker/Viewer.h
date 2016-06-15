#pragma once
#include "smart_ptr.h"
#include <string>

PTR( Viewer );
PTR( ModelManager );
PTR( Camera );
PTR( Model );

class Viewer {
public:
	Viewer( );
	virtual ~Viewer();
public:
	void draw( );
	void setModel( );
private:
	ModelManagerPtr _model_manager;
	ModelPtr _model;
	CameraPtr _camera;
};

