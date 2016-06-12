#include "Ground.h"

Ground::Ground( ) {
	
}

Ground::~Ground( ) {
}

GROUND_CHIP_TYPE Ground::getGroundChip( int mx, int my ) const {
	return _data[ my * _width + mx ];
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
	if ( !_data.empty( ) ) {
		_width = 0;
		_height = 0;
		_data.clear( );
	}
	FILE* fp;
	fopen_s( &fp,"../resource2D/map.grd", "r" );
	fscanf_s( fp, "%d", &_width );
	fscanf_s( fp, "%d", &_height );
	for ( int i = 0; i < _width * _height; i++ ) {
		int data;
		fscanf_s( fp, "%d", &data );
		_data.push_back( data );
	}
	fclose( fp );
}