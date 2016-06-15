#pragma once
#include "Model.h"
#include "mathmatics.h"
#include "smart_ptr.h"
#include <array>
#include <string>

PTR( ModelManager );

class ModelManager {
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
		std::array< Model::VERTEX, 131072 > vertex_array;
		int vertex_count;
	};
public:
	ModelManager( );
	virtual ~ModelManager( );
public:
	Model::VERTEX getVERTEX( int idx );
	int getVertexNum( );
	ModelData getData( );
	void loadModelData( const char * filename );
	void saveModelData( const char * filename );
	void setModelPos( int x, int z );
	void setVertex( Model::VERTEX vertex );
private:
	void loadXFileModelData( const char * filename );
	void loadMdlModelData( const char * filename );
private:
	Matrix _matrix;
	std::array< Vector, 2048 > _point_array;
	std::array< Vector, 2048 > _nomals_point_array;
	std::array< Index, 1024 > _index_array;
	std::array< Index, 1024 > _nomals_index_array;
	std::array< Uv, 2048 > _texture_array;
	std::array< int, 1024 > _material_array;
	ModelData _data;
	int _index_num;
};

