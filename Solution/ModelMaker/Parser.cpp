#include "Parser.h"
#include "Model.h"
#include "DxLib.h"

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

	int _settingCounter = 0;

	int point_num = 0;
	
	int nomals_index_num = 0;
	int nomals_point_num = 0;
	int texture_num = 0;
	int mat_num = 0;
	MODE mode = MODE_SEECK_SEARCH;

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
				_matrix.data[ mat_num ][0] = dat_1;
				_matrix.data[ mat_num ][1] = dat_2;
				_matrix.data[ mat_num ][2] = dat_3;
				_matrix.data[ mat_num ][3] = dat_4;

				mat_num++;
				if ( str.find( "Mesh" ) != -1 ) {
					FileRead_gets( buf, 1024, fh );
					sscanf_s( buf, "%d,", &point_num );
					mode = MODE_READ_POINT;
				}
				break;
			case MODE_READ_POINT: 
			{
				double x;
				double y;
				double z;
				sscanf_s( buf, "%lf;%lf;%lf;,", &x, &y, &z );
				_point_array[ _settingCounter ] = Vector( x, y, z );
				_settingCounter++;
				if ( _settingCounter == point_num ) {
					FileRead_gets( buf, 1024, fh );
					mode = MODE_READ_INDEX;
					sscanf_s( buf, "%d;", &_index_num );
					_settingCounter = 0;
				}
				}
				break;
			case MODE_READ_INDEX:
				{
				int polygon;
				int point_1;
				int point_2;
				int point_3;
				sscanf_s( buf, "%d;%d,%d,%d;,", &polygon, &point_1, &point_2, &point_3 );
				_index_array[ _settingCounter ].polygon = polygon;
				_index_array[ _settingCounter ].index[ 0 ] = point_1;
				_index_array[ _settingCounter ].index[ 1 ] = point_2;
				_index_array[ _settingCounter ].index[ 2 ] = point_3;
				_settingCounter++;
				if ( _index_num == _settingCounter ) {
					FileRead_gets( buf, 1024, fh );
					FileRead_gets( buf, 1024, fh );
					sscanf_s( buf, "%d,", &nomals_point_num );
					mode = MODE_READ_NORMALS_POINT;
					_settingCounter = 0;
				}
				}
				break;
			
			case MODE_READ_NORMALS_POINT:
				{
				double x;
				double y;
				double z;
				sscanf_s( buf, "%lf;%lf;%lf;,", &x, &y, &z );
				_nomals_point_array[ _settingCounter ] = Vector( x, y, z );
				_settingCounter++;
				if ( _settingCounter == nomals_point_num ) {
					FileRead_gets( buf, 1024, fh );
					sscanf_s( buf, "%d,", &nomals_index_num );
					mode = MODE_READ_NORMALS_INDEX;
					_settingCounter = 0;
				}
				}
				break;
			case MODE_READ_NORMALS_INDEX:
				{
				int polygon;
				int point_1;
				int point_2;
				int point_3;
				sscanf_s( buf, "%d;%d,%d,%d;,", &polygon, &point_1, &point_2, &point_3 );
				_nomals_index_array[ _settingCounter ].polygon = polygon;
				_nomals_index_array[ _settingCounter ].index[ 0 ] = point_1;
				_nomals_index_array[ _settingCounter ].index[ 1 ] = point_2;
				_nomals_index_array[ _settingCounter ].index[ 2 ] = point_3;
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

