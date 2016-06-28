#include "Camera.h"
#include "Framework.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "ModelMaker.h"
#include "Model.h"

const Vector START_TO_POS = Vector( 0, 40, 40 );

CameraPtr Camera::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Camera >( fw->getTask( getTag( ) ) );
}

Camera::Camera( ) {
	_to_pos = START_TO_POS;
	_before_mouse_pos = _to_pos;

	FrameworkPtr fw = Framework::getInstance( );
	fw->setCameraUp( Vector( 0.0, 0.0, 1.0 ) );
	fw->setCamera( _target + _to_pos, _target );
}

Camera::~Camera( ) {
}

void Camera::update( ) {
	// マウスの左右でZ軸回転をするように
	FrameworkPtr fw = Framework::getInstance( );
	MousePtr mouse = Mouse::getTask( );
	KeyboardPtr keyboard = Keyboard::getTask( );

	Vector mouse_pos = mouse->getPos( );

	Vector diff = _before_mouse_pos - mouse_pos;
	_before_mouse_pos = mouse_pos;

	if ( diff.x != 0 ) {
		double angle = ( 10 * PI / 180 ) * diff.normalize( ).x;
		Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), angle );
		_to_pos = mat.multiply( _to_pos );
	}

	if ( diff.y != 0 ) {
		Vector axis = _to_pos.cross( Vector( 0.0, 0.0, 1.0 ) );
		double angle = ( 5 * PI / 180 ) * diff.normalize( ).y;
		Matrix mat = Matrix::makeTransformRotation( axis, angle );
		_to_pos = mat.multiply( _to_pos );
	}

	int wheel = mouse->getWheelRotValue( );
	if ( wheel != 0 ) {
		double length = _to_pos.getLength( );
		length += wheel;
		if ( length < 10 ) {
			length = 10;
		}
		_to_pos = _to_pos.normalize( ) * length;
	}

	if ( keyboard->isPushKey( "ENTER" ) ) {
  		_to_pos = START_TO_POS;
	}

	Vector vec;
	if ( keyboard->isHoldKey( "ARROW_UP" ) ) {
		vec = _to_pos;
		vec.z = 0;
		vec *= -1;
	}

	if ( keyboard->isHoldKey( "ARROW_DOWN" ) ) {
		vec = _to_pos;
		vec.z = 0;
	}

	if ( keyboard->isHoldKey( "ARROW_LEFT" ) ) {
		vec = _to_pos;
		vec.z = 0;
		vec = _to_pos.cross( Vector( 0, 0, -1 ) );
	}
	
	if ( keyboard->isHoldKey( "ARROW_RIGHT" ) ) {
		vec = _to_pos;
		vec.z = 0;
		vec = _to_pos.cross( Vector( 0, 0, 1 ) );
	}
	

	_target += vec.normalize( ) * 0.1;

	fw->setCamera( _target + _to_pos, _target );
}