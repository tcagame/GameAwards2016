#include "DxLib.h"
#include "Framework.h"

void main( );

int WINAPI WinMain( HINSTANCE hInstaece, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) {
	Framework::initialize( );
	main( );
	Framework::getInstance( )->run( );
	Framework::finalize( );
	return 0;
}