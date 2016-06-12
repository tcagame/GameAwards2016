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
	struct ModelData { 
		std::array< Model::VERTEX, 8192 > vertex_array;
		int polygon_num;
	};
public:
	FileManager( );
	virtual ~FileManager( );
public:
	Model::VERTEX getVERTEX( int idx );
	int getPolygonNum( );
	void loadData( int x, int y, const char * filename );
	void saveModelData( const char * filename );
private:
	void loadXFileModelData( const char * filename );
	void loadMdlModelData( const char * filename );
	void setVERTEX( int x, int y );

private:
	std::array< Vector, 2048 > _point_array;
	std::array< Vector, 2048 > _nomals_point_array;
	std::array< Index, 1024 > _index_array;
	std::array< Index, 1024 > _nomals_index_array;
	std::array< Uv, 2048 > _texture_array;
	std::array< int, 1024 > _material_array;
	ModelData _data;
	int _vertex_count;
	int _index_num;
};

