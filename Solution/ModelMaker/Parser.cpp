#include "Parser.h"
#include "Model.h"
#include "DxLib.h"
#include <vector>
#include <array>
#include <assert.h>

Parser::Parser( ) {
}


Parser::~Parser( ) {
}

bool Parser::load( std::string filename ) {
	enum MODE {
		MODE_SEECK_SEARCH,
		MODE_READ_MATRIX,
		MODE_READ_POINT,
		MODE_READ_INDEX,
		MODE_READ_NORMALS_POINT,
		MODE_READ_NORMALS_INDEX,
		MODE_READ_TEXTURE,
		MODE_READ_MATERIAL,
	};

	int fh = FileRead_open( filename.c_str( ) );
	if ( fh == -1 ) {
		return false;
	}

	int texture_num = 0;
	int mat_num = 0;
	MODE mode = MODE_SEECK_SEARCH;
	Matrix matrix;

	int point_num = 0;
	std::vector< Vector > point_array;

	struct Index {
		std::array< unsigned int, 3 > idx;
	};

	int point_index_num = 0;
	std::vector< Index > point_index_array;

	int normal_num = 0;
	std::vector< Vector > normal_array;
	
	int normal_index_num;
	std::vector< Index > normal_index_array;

	while ( FileRead_eof( fh ) == 0 ) {
		char buf[ 1024 ];
		FileRead_gets( buf, 1024, fh );
		std::string str = buf;
		switch( mode ) {
			
			case MODE_SEECK_SEARCH:
				if ( str.find( "FrameTransformMatrix" ) != -1 ) {
					mode = MODE_READ_MATRIX;
				}
				break;
			case MODE_READ_MATRIX:
				double dat_1;
				double dat_2;
				double dat_3;
				double dat_4;
				if ( mat_num < 4 ) {
					sscanf_s( buf, "%lf,%lf,%lf,%lf,", &dat_1, &dat_2, &dat_3, &dat_4 );
				}
				matrix.data[ mat_num ][0] = dat_1;
				matrix.data[ mat_num ][1] = dat_2;
				matrix.data[ mat_num ][2] = dat_3;
				matrix.data[ mat_num ][3] = dat_4;

				mat_num++;
				if ( str.find( "Mesh" ) != -1 ) {
					FileRead_gets( buf, 1024, fh );
					sscanf_s( buf, "%d,", &point_num );
					mode = MODE_READ_POINT;
				}
				break;
			case MODE_READ_POINT: {
				double x;
				double y;
				double z;
				sscanf_s( buf, "%lf;%lf;%lf;,", &x, &y, &z );
				point_array.push_back( Vector( x, y, z ) );
				if ( point_array.size( ) == point_num ) {
					FileRead_gets( buf, 1024, fh );
					mode = MODE_READ_INDEX;
					sscanf_s( buf, "%d;", &point_index_num );
				}
				break;
			}
			case MODE_READ_INDEX: {
				int polygon;
				int point_1;
				int point_2;
				int point_3;
				sscanf_s( buf, "%d;%d,%d,%d;,", &polygon, &point_1, &point_2, &point_3 );
				assert( polygon == 3 );
				Index index;
				index.idx[ 0 ] = point_1;
				index.idx[ 1 ] = point_2;
				index.idx[ 2 ] = point_3;
				point_index_array.push_back( index );
				if ( point_index_num == point_index_array.size( ) ) {
					FileRead_gets( buf, 1024, fh );
					FileRead_gets( buf, 1024, fh );
					sscanf_s( buf, "%d,", &normal_num );
					mode = MODE_READ_NORMALS_POINT;
				}
				break;
			}
			case MODE_READ_NORMALS_POINT: {
				double x;
				double y;
				double z;
				sscanf_s( buf, "%lf;%lf;%lf;,", &x, &y, &z );
				normals_array.push_back( Vector( x, y, z ) );
				_settingCounter++;
				if ( normals_array.size( ) == normal_num ) {
					FileRead_gets( buf, 1024, fh );
					sscanf_s( buf, "%d,", &nomals_index_num );
					mode = MODE_READ_NORMALS_INDEX;
				}
				break;
			}
			case MODE_READ_NORMALS_INDEX: {
				int polygon;
				int point_1;
				int point_2;
				int point_3;
				sscanf_s( buf, "%d;%d,%d,%d;,", &polygon, &point_1, &point_2, &point_3 );
				assert( polygon == 3 );
				normal_index_array[ _settingCounter ].index[ 0 ] = point_1;
				normal_index_array[ _settingCounter ].index[ 1 ] = point_2;
				normal_index_array[ _settingCounter ].index[ 2 ] = point_3;
				_settingCounter++;
				if (  nomals_index_num == _settingCounter ) {
					FileRead_gets( buf, 1024, fh );
					FileRead_gets( buf, 1024, fh );
					FileRead_gets( buf, 1024, fh );
					sscanf_s( buf, "%d,", &texture_num );
					mode = MODE_READ_TEXTURE;
					_settingCounter = 0;
				}
				}
				break;
			case MODE_READ_TEXTURE:
				{
				float u;
				float v;
				sscanf_s( buf, "%f;%f;,", &u, &v );
				_texture_array[ _settingCounter ].u = u;
				_texture_array[ _settingCounter ].v = v;
				_settingCounter++;
				if (  _settingCounter == texture_num ) {
					FileRead_gets( buf, 1024, fh );
					FileRead_gets( buf, 1024, fh );
					mode = MODE_READ_MATERIAL;
					_settingCounter = 0;
				}
				}
				break;
			case MODE_READ_MATERIAL:
				{
				int material;
				sscanf_s( buf, "%d;,", &material );
				_material_array[ _settingCounter ] = material;
				_settingCounter++;
				if (  str.find( "}" ) != -1 ) {
					FileRead_gets( buf, 1024, fh );
					mode = MODE_READ_MATERIAL;
					_settingCounter = 0;
				}
				}
				break;
		}
	
	}

	FileRead_close( fh );
}
ModelPtr Parser::makeModel( ) {
	ModelPtr model;

	return model;
}

