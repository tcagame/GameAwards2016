#include "Framework.h"
#include "ModelMaker.h"

int main( ) {
	FrameworkPtr fw = Framework::getInstance( );
	ModelMakerPtr model_maker = ModelMakerPtr( new ModelMaker( ) );


	fw->addTask( ModelMaker::getTag( ), model_maker );

}