#include "Framework.h"
#include "ModelMaker.h"
#include "Keyboard.h"

int main( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ModelMakerPtr model_maker = ModelMakerPtr( new ModelMaker( ) );
	KeyboardPtr keyboard = KeyboardPtr( new Keyboard );

	fw->addTask( ModelMaker::getTag( ), model_maker );
	fw->addTask( Keyboard::getTag( ), keyboard );
}