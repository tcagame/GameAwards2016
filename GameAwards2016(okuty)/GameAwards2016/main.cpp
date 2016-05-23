#include "Framework.h"
#include "App.h"
#include "Viewer.h"
#include "Drawer.h"
#include "Mouse.h"
#include "Keyboard.h"

void main( ) {
	
	FrameworkPtr fw = Framework::getInstance( );
	AppPtr      app      = AppPtr     ( new App      );
	ViewerPtr   viewer   = ViewerPtr  ( new Viewer   );
	DrawerPtr   drawer   = DrawerPtr  ( new Drawer   );
	MousePtr    mouse    = MousePtr   ( new Mouse    );
	KeyboardPtr keyboard = KeyboardPtr( new Keyboard );
	fw->addTask( App     ::getTag( ), app      );
	fw->addTask( Viewer  ::getTag( ), viewer   );
	fw->addTask( Drawer  ::getTag( ), drawer   );
	fw->addTask( Mouse   ::getTag( ), mouse    );
	fw->addTask( Keyboard::getTag( ), keyboard );
}