#include "Framework.h"
#include "GroundMaker.h"


int main( ) {
	FrameworkPtr fw = Framework::getInstance( );
	GroundMakerPtr ground_maker = GroundMakerPtr( new GroundMaker( ) );
	
	fw->addTask( GroundMaker::getTag( ), ground_maker );
}