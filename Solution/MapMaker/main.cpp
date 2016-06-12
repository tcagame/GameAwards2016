#include "Framework.h"
#include "MapMaker.h"
#include "Drawer.h"
#include "Viewer.h"

int main( ) {
	FrameworkPtr fw = Framework::getInstance( );
	DrawerPtr   drawer   = DrawerPtr  ( new Drawer( "Resource2D" )   );
	MapMakerPtr map_maker = MapMakerPtr( new MapMaker( ) );
	ViewerPtr viewer = ViewerPtr( new Viewer( map_maker ) );


	fw->addTask( Drawer::getTag( ), drawer );
	fw->addTask( Viewer::getTag( ), viewer );
}