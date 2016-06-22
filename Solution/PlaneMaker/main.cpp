#include "Framework.h"
#include "PlaneMaker.h"

int main( ) {
	FrameworkPtr fw = Framework::getInstance( );
	PlaneMakerPtr plane_maker = PlaneMakerPtr( new PlaneMaker( ) );
	fw->terminate( );
}