#pragma once

#include "smart_ptr.h"
#include "Task.h"
#include <string>
#include <map>

PTR( Framework );
PTR( Binary );

class Framework {
public:
	Framework( );
	virtual ~Framework( );
public:
	static void initialize( );
	static void finalize( );
	static FrameworkPtr getInstance( );
public:
	void run( );
	void addTask( std::string tag, TaskPtr task );
	TaskPtr getTask( std::string tag );
	int getWindowWidth( ) const;
	int getWindowHeight( ) const;
	void loadBinary( const char * filename, BinaryPtr binary );
	void saveBinary( const char * filename, BinaryPtr binary );
	std::string inputString( int sx, int sy );
	void terminate( );
private:
	static FrameworkPtr _instance;
	int _screen_width;
	int _screen_height;
	std::map< std::string, TaskPtr > _task_list;
	bool _terminating;
};

