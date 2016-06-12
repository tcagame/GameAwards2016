#pragma once
#include "smart_ptr.h"
#include "MapChip.h"
#include <vector>
#include <string>

PTR( GroundMaker );
PTR( ModelMaker );
PTR( MapMaker );

class MapMaker {
public:
	MapMaker( );
	virtual ~MapMaker( );
public:
	int getWidth( ) const;
	int getHeight( ) const;
	MAP_TYPE getMapType( int mx, int my, MAP_TYPE type ) const;
private:
	void putFileName( );
	void load( );
	void mapMake( );
	void save( );
	void makeMountain( int mx, int my );
	void makeRiver( int mx, int my );
	void makePlane( int mx, int my );
	void makeDesert( int mx, int my );
private:
	std::string _file_name;
	ModelMakerPtr _model_maker;
	GroundMakerPtr _ground_maker;

	int _map_width;
	int _map_height;
	std::vector< MAP_TYPE > _plane_map;
	std::vector< MAP_TYPE > _desert_map;
	std::vector< MAP_TYPE > _mountain_map;
	std::vector< MAP_TYPE > _river_map;
};