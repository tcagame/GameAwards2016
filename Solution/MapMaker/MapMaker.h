#pragma once
#include "smart_ptr.h"
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
	void putFileName( );
	void load( );
	void mapMake( );
	void save( );
private:
	void makeMountain( );
	void makeRiver( );
	void makePlane( );
	void makeDesert( );
private:
	std::string _file_name;
	ModelMakerPtr _model_maker;
	GroundMakerPtr _ground_maker;

	int _map_width;
	int _map_height;
	std::vector< unsigned char > _plane_map;
	std::vector< unsigned char > _desert_map;
	std::vector< unsigned char > _mountain_map;
	std::vector< unsigned char > _river_map;
};