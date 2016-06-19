#include "Framework.h"
#include "Binary.h"
#include "DxLib.h"

const int COLOR_BIT = 32;
const int COLOR_BIT_DEPTH = 32;
const int FPS = 60;
const char* WINDOW_NAME = "ゲーム大賞";

FrameworkPtr Framework::_instance;

Framework::Framework( ) {
	int sx = GetSystemMetrics( SM_CXSCREEN );
	int sy = GetSystemMetrics( SM_CYSCREEN );
#if FULLSCREEN
	ChangeWindowMode( FALSE );
	SetGraphMode( sx, sy, COLOR_BIT, FPS );
	_screen_width = sx;
	_screen_height = sy;
#else
	sx = sx * 3 / 4;
	sy = sy * 3 / 4;
	ChangeWindowMode( TRUE );
	SetGraphMode( sx, sy, COLOR_BIT_DEPTH, FPS );
	_screen_width = sx;
	_screen_height = sy;
#endif
	SetWindowText( WINDOW_NAME );
	if ( DxLib_Init( ) == -1 ) {
		return;
	}
	//SetUseSetDrawScreenSettingReset(FALSE);
	SetUseLighting( FALSE );
	SetLightEnable( FALSE );
	SetUseZBuffer3D( TRUE );
	SetWriteZBuffer3D( TRUE );
	SetDrawScreen( DX_SCREEN_BACK );
	SetupCamera_Perspective( 12.0f * DX_PI_F / 180.0f );
	SetCameraNearFar( 10.0f, 10000.0f );
	SetAlwaysRunFlag( TRUE ) ;
	SetUseBackCulling( TRUE ) ;
    SetTextureAddressModeUV( DX_TEXADDRESS_WRAP, DX_TEXADDRESS_WRAP );

	_terminating = false;
}

Framework::~Framework( ) {
	DxLib_End( );
}

void Framework::initialize( ) {
	if ( !_instance ) {
		_instance = FrameworkPtr( new Framework );
	}
}

void Framework::finalize( ) {
	if ( _instance ) {
		_instance.reset( );
	}
}

FrameworkPtr Framework::getInstance( ) {
	return _instance;
}

void Framework::run( ) {
	// 初期化
	{
		std::map< std::string, TaskPtr >::iterator ite = _task_list.begin( );
		while ( ite != _task_list.end( ) ) {
			TaskPtr task = ite->second;
			task->initialize( );
			ite++;
		}
	}

	// メインループ
	while ( true ) {
		if ( _terminating ) {
			break;
		}
		if ( ProcessMessage( ) != 0 ) {
			break;
		}
		if ( CheckHitKey( KEY_INPUT_ESCAPE ) ) {
			break;
		}

		std::map< std::string, TaskPtr >::iterator ite = _task_list.begin( );
		while ( ite != _task_list.end( ) ) {
			TaskPtr task = ite->second;
			task->update( );
			ite++;
		}
	}

	// 終了処理
	{
		std::map< std::string, TaskPtr >::iterator ite = _task_list.begin( );
		while ( ite != _task_list.end( ) ) {
			TaskPtr task = ite->second;
			task->finalize( );
			ite++;
		}
	}
}

void Framework::addTask( std::string tag, TaskPtr task ) {
	if ( task ) {
		_task_list[ tag ] = task;
	}
}

TaskPtr Framework::getTask( std::string tag ) {
	if( _task_list.find( tag ) == _task_list.end( ) ) {
		return TaskPtr( );
	}
	return _task_list[ tag ];
}

int Framework::getWindowWidth( ) const  {
	return _screen_width;
}

int Framework::getWindowHeight( ) const  {
	return _screen_height;
}

void Framework::loadBinary( const char * filename, BinaryPtr binary ) {
	std::string str = filename;

	int size = ( int )FileRead_size( filename );
	if ( size == -1 ) {
		str = "../" + str;
		size = ( int )FileRead_size( filename );
		if ( size == -1 ) {
			return;
		}
	}

	int handle = FileRead_open( str.c_str( ) );
	if ( handle == -1 ) {
		return;
	}

	binary->ensure( size );

	FileRead_read( binary->getPtr( ), size, handle );

	FileRead_close( handle );
}


void Framework::saveBinary( const char * filename, BinaryPtr binary ) {

	int size = binary->getSize( );
	if ( size <= 0 ) {
		return;
	}
	
	FILE *fp;
	errno_t err = fopen_s( &fp, filename, "wb" );
	if ( err != 0 ) {
		return;
	}

	fwrite( binary->getPtr( ), size, 1, fp );
	fclose( fp );
}

std::string Framework::inputString( int sx, int sy ) {
	char buf[ 2048 ];
	std::string str;
	if ( KeyInputString( sx, sy, 2048, buf, TRUE ) == TRUE ) {
		str = buf;
	}
	return str;
}

void Framework::terminate( ) {
	_terminating = true;
}

void Framework::setCameraUp( const Vector& up ) {
	_camera_up = up;
}

void Framework::setCamera( const Vector& pos, const Vector& target ) {
	DxLib::VECTOR dx_pos = VGet( float( pos.x ), float( pos.y ), float( pos.z ) );
	DxLib::VECTOR dx_target = VGet( float( target.x ), float( target.y ), float( target.z ) );
	DxLib::VECTOR dx_up = VGet( float( _camera_up.x ), float( _camera_up.y ), float( _camera_up.z ) );
	SetCameraPositionAndTargetAndUpVec( dx_pos, dx_target, dx_up );
}