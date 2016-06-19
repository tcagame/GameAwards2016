#include "Framework.h"
#include "ModelMaker.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Camera.h"

int main( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ModelMakerPtr model_maker = ModelMakerPtr( new ModelMaker( ) );
	KeyboardPtr keyboard = KeyboardPtr( new Keyboard );
	MousePtr mouse = MousePtr( new Mouse );
	CameraPtr camera = CameraPtr( new Camera );

	fw->addTask( ModelMaker::getTag( ), model_maker );
	fw->addTask( Keyboard::getTag( ), keyboard );
	fw->addTask( Mouse::getTag( ), mouse );
	fw->addTask( Camera::getTag( ), camera );
}