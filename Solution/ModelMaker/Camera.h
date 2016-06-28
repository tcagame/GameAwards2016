#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include "mathmatics.h"
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
	Vector _to_pos;
	Vector _target; // pos = _target + _to_pos;
	Vector _before_mouse_pos;
};

