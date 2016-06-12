#include "Camera.h"
#include "Framework.h"


CameraPtr Camera::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Camera >( fw->getTask( getTag( ) ) );
}

Camera::Camera( ) {
}


Camera::~Camera( ) {
}

void Camera::update( ) {
		_camera_x = _r * sin( _angle_xz * DX_PI / 180 );
		_camera_z = _r * cos( _angle_xz * DX_PI / 180 );
		if ( CheckHitKey( KEY_INPUT_LEFT ) ) {
			_angle_xz += 2;
		}
		if ( CheckHitKey( KEY_INPUT_RIGHT ) ) {
			_angle_xz -= 2;
		}
		if ( CheckHitKey( KEY_INPUT_Z ) ) {
			_r -= 2;
		}
		if ( CheckHitKey( KEY_INPUT_X ) ) { 
			_r += 2;
		}
		if ( CheckHitKey( KEY_INPUT_UP ) ) {
			_camera_y++;
		}
		if ( CheckHitKey( KEY_INPUT_DOWN ) ) {
			_camera_y--;
		}

		SetCameraPositionAndTarget_UpVecY( VGet( float( _camera_x ), float( _camera_y ), float( _camera_z ) ), VGet( 0.0f, 0.0f, 0.0f ) );
}