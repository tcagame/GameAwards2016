#pragma once

#include "task.h"
#include <string>
#include <array>

PTR( Drawer );

class Drawer : public Task {
public:
	static DrawerPtr getTask( );
	static std::string getTag( ) { return "DRAWER"; }
public:
	Drawer( const char * directory );
	virtual ~Drawer( );
public:
	enum BLEND {
		BLEND_NONE,
		BLEND_ALPHA,
		BLEND_ADD,
		MAX_BLEND,
	};
	struct Transform {
		int sx;
		int sy;
		int tx;
		int ty;
		int tw;
		int th;
		Transform( );
		Transform( int sx_, int sy_, int tx_ = -1, int ty_ = -1, int tw_ = -1, int th_ = -1 );
	};

	struct Sprite {
		Transform trans;
		int res;
		BLEND blend;
		double ratio;
		Sprite( );
		Sprite( Transform trans_, int res_, BLEND blend_ = BLEND_NONE, double ratio_ = 1.0 );
	};
public:
	void load( int res, const char * filename );
	void set( const Sprite& sprite );
	void update( );
private:
	static const int ID_NUM = 100;
	static const int SPRITE_NUM = 2000;
	const char * _directory;
	std::array< Sprite, SPRITE_NUM > _sprite;
	std::array< int, ID_NUM > _id;
	int _sprite_idx;
	
};

