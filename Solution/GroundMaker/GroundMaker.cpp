#include "GroundMaker.h"


GroundMaker::GroundMaker( ) {
}

GroundMaker::~GroundMaker( ) {
}

void GroundMaker::load(  ) {
	FILE* fp;
	//CSV‚©‚çƒOƒ‰ƒEƒ“ƒh‚É•ÏŠ·
	_file_name = "../" + _file_name;
	fopen_s( &fp, _file_name.c_str( ), "r" );
	fscanf_s( fp, "%d", &_width );
	fscanf_s( fp, "%d", &_height );
	for ( int i = 0; i < _width * _height; i++ ) {
		int data;
		fscanf_s( fp, "%d", &data );
		_data.push_back( data );
	}
	fclose( fp );
}

void GroundMaker::save( ) {
	FILE* fp;
	fopen_s( &fp,"../map.grd", "w" );
	fprintf( fp, "%d\n", _width );
	fprintf( fp, "%d\n", _height );
	for ( int i = 0; i < _width * _height; i++ ) {
		fprintf( fp, "%d\n", _data[ i ] );
	}
	fclose( fp );
}
