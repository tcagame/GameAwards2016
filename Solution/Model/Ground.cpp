#include "Ground.h"

Ground::Ground( ) {
	
}

Ground::~Ground( ) {
}

GROUND_CHIP_TYPE Ground::getGroundChip( int idx ) const {
	return _data[ idx ];
}

int Ground::getWidth( ) const{
	return _width;
}

int Ground::getHeight( ) const{
	return _height;
}

void Ground::load( ) {
	FILE* fp;
	fopen_s( &fp,"../map.grd", "r" );
	fscanf_s( fp, "%d", &_width );
	fscanf_s( fp, "%d", &_height );
	for ( int i = 0; i < _width * _height; i++ ) {
		int data;
		fscanf_s( fp, "%d", &data );
		_data.push_back( data );
	}
	fclose( fp );
}