#include "Camera.h"
#include "Framework.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "ModelMaker.h"
#include "Model.h"

const Vector START_POS = Vector( 0, 20, 20 );

CameraPtr Camera::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Camera >( fw->getTask( getTag( ) ) );
}

Camera::Camera( ) {
	_pos = START_POS;
	_before_mouse_pos = _pos;

	FrameworkPtr fw = Framework::getInstance( );
	fw->setCameraUp( Vector( 0.0, 0.0, 1.0 ) );
	fw->setCamera( _pos, Vector( 0.0, 0.0, 0.0 ) );
}

Camera::~Camera( ) {
}

void Camera::update( ) {
	// ƒ}ƒEƒX‚Ì¶‰E‚ÅZŽ²‰ñ“]‚ð‚·‚é‚æ‚¤‚É
	FrameworkPtr fw = Framework::getInstance( );
	MousePtr mouse = Mouse::getTask( );
	KeyboardPtr keyboard = Keyboard::getTask( );

	Vector mouse_pos = mouse->getPos( );

	Vector diff = _before_mouse_pos - mouse_pos;
	_before_mouse_pos = mouse_pos;

	if ( diff.x != 0 ) {
		double angle = ( 10 * PI / 180 ) * diff.normalize( ).x;
		Matrix mat = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), angle );
		_pos = mat.multiply( _pos );
	}

	if ( diff.y != 0 ) {
		Vector axis = _pos.cross( Vector( 0.0, 0.0, 1.0 ) );
		double angle = ( 5 * PI / 180 ) * diff.normalize( ).y;
		Matrix mat = Matrix::makeTransformRotation( axis, angle );
		_pos = mat.multiply( _pos );
	}

	int wheel = mouse->getWheelRotValue( );
	if ( wheel != 0 ) {
		double length = _pos.getLength( );
		length += wheel;
		if ( length < 10 ) {
			length = 10;
		}
		_pos = _pos.normalize( ) * length;
	}

	ModelMakerPtr model_maker = ModelMaker::getTask( );
	if ( keyboard->isPushKey( "X" ) ) {
		Matrix matrix = Matrix::makeTransformRotation( Vector( 1, 0, 0 ), PI2 / 4 ); // XŽ²‚É90“x‰ñ“]
		model_maker->transferModel( matrix );
	}

	if ( keyboard->isPushKey( "Y" ) ) {
		Matrix matrix = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI2 / 4 ); // XŽ²‚É90“x‰ñ“]
		model_maker->transferModel( matrix );
	}

	if ( keyboard->isPushKey( "Z" ) ) {
		Matrix matrix = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), PI2 / 4 ); // XŽ²‚É90“x‰ñ“]
		model_maker->transferModel( matrix );
	}

	if ( keyboard->isPushKey( "ENTER" ) ) {
  		_pos = START_POS;
	}
	fw->setCamera( _pos, Vector( 0, 0, 0 ) );
}