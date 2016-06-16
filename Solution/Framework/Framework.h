#pragma once
#include <string>
#include <map>
#include "smart_ptr.h"
#include "Task.h"

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
	bool inputString( int sx, int sy, char *buf, int size );
public:
	static FrameworkPtr _instance;
private:
	int _screen_width;
	int _screen_height;
public:
	std::map< std::string, TaskPtr > _task_list;
};

