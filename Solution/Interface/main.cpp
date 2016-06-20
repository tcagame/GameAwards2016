#include "Framework.h"
#include "Mouse.h"
#include "Camera.h"

void main( ) {

	FrameworkPtr fw = Framework::getInstance ( );
	MousePtr mouse = MousePtr( new Mouse( ) );
	CameraPtr camera = CameraPtr ( new Camera( ) );

	fw->addTask( Mouse::getTag( ), mouse );
	fw->addTask( Camera::getTag( ), camera );
}
