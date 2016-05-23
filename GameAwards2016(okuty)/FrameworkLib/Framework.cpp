#include "Framework.h"
#include "DxLib.h"

const int COLOR_BIT = 32;
const int COLOR_BIT_DEPTH = 32;
const int FPS = 60;
const char* WINDOW_NAME = "�Q�[�����";

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
	SetDrawScreen( DX_SCREEN_BACK );
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
	// ������
	{
		std::map< std::string, TaskPtr >::iterator ite = _task_list.begin( );
		while ( ite != _task_list.end( ) ) {
			TaskPtr task = ite->second;
			task->initialize( );
			ite++;
		}
	}

	// ���C�����[�v
	while ( true ) {
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

	// �I������
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
