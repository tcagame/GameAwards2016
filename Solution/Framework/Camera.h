#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include "DxLib.h"
#include <string>


PTR( Camera );
class Camera : public Task {
public:
	static CameraPtr getTask( );
	static std::string getTag( ) { return "CAMERA"; }
public:
	Camera();
	virtual ~Camera();
public:
	void update( );
private:
	double _angle;
	double _camera_x = 0;
	double _camera_y = 0;
	double _camera_z = -100;
	double _angle_xz = 0;
	double _r = 50;
};

