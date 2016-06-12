#include "Framework.h"
#include "MapMaker.h"
#include "Drawer.h"
#include "Viewer.h"
#include "ModelManager.h"
#include "FileManager.h"
#include "Model.h"
#include "Camera.h"

int main( ) {
	FrameworkPtr fw = Framework::getInstance( );
	DrawerPtr   drawer   = DrawerPtr  ( new Drawer( "Resource2D" )   );
	MapMakerPtr map_maker = MapMakerPtr( new MapMaker( ) );
	FileManagerPtr file_manager = FileManagerPtr( new FileManager(  ) );
	ModelPtr model = ModelPtr( new Model(  ) );
	CameraPtr camera = CameraPtr( new Camera( ) );
	ModelManagerPtr model_manager = ModelManagerPtr( new ModelManager( map_maker, file_manager, model ) );
	ViewerPtr viewer = ViewerPtr( new Viewer( map_maker, file_manager, model ) );

	fw->addTask( Drawer::getTag( ), drawer );
	fw->addTask( Viewer::getTag( ), viewer );
	fw->addTask( Camera::getTag( ), camera );

}