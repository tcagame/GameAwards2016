#include "Camera.h"
#include "Framework.h"
#include "Mouse.h"

const Vector START_POS = Vector( 0, 20, 20 );

CameraPtr Camera::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Camera >( fw->getTask( getTag( ) ) );
}

Camera::Camera( ) {
	_pos = START_POS;

	FrameworkPtr fw = Framework::getInstance( );
	fw->setCameraUp( Vector( 0.0, 0.0, 1.0 ) );
	fw->setCamera( _pos, Vector( 0.0, 0.0, 0.0 ) );
}

Camera::~Camera( ) {
}

void Camera::update( ) {
	FrameworkPtr fw = Framework::getInstance( );
	MousePtr mouse = Mouse::getTask( );

	int wheel = mouse->getWheelRotValue( );
	if ( wheel != 0 ) {
		double length = _pos.getLength( );
		length += wheel;
		if ( length < 10 ) {
			length = 10;
		}
		_pos = _pos.normalize( ) * length;
	}

	
	fw->setCamera( _pos, Vector( 0, 0, 0 ) );
}