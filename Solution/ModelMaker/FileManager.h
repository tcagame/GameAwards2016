#pragma once
#include "Model.h"
#include "mathmatics.h"
#include "smart_ptr.h"
#include <array>
#include <string>

PTR( FileManager );

class FileManager {
public:
	struct Index {
		int polygon;
		std::array< int, 3 > index;
	};
	
	struct Uv {
		float u;
		float v;
	};

public:
	FileManager( );
	virtual ~FileManager( );
public:
	Model::VERTEX getVERTEX( int idx );
	int getPolygonNum( );
private:
	void loadModelData( );
	void setVERTEX( );
private:
	std::array< Vector, 2048 > _point_array;
	std::array< Vector, 2048 > _nomals_point_array;
	std::array< Index, 1024 > _index_array;
	std::array< Index, 1024 > _nomals_index_array;
	std::array< Uv, 2048 > _texture_array;
	std::array< int, 1024 > _material_array;
	std::array< Model::VERTEX, 4096 > _VERTEX_array;
	int _polygon_num;

};

