#pragma once
#include "smart_ptr.h"
#include <string>

PTR( Viewer );
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
	ModelPtr _model;
	CameraPtr _camera;
	int _texture;
};

