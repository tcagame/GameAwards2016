#include "DxLib.h"
#include "Framework.h"
#include "Mouse.h"

void main( );

int WINAPI WinMain( HINSTANCE hInstaece, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	Framework::initialize( );

	MousePtr mouse = MousePtr( new Mouse( ) );
	Framework::getInstance( )->addTask( Mouse::getTag( ), mouse );

	main( );
	Framework::getInstance( )->run( );
	Framework::finalize( );
	return 0;
}