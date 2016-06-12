#include "GroundMaker.h"

GroundMaker::GroundMaker( ) {
	_height = 0;
	_width = 0;
	loadToCSV( "map" );
	save( );
}

GroundMaker::~GroundMaker( ) {
}

void GroundMaker::loadToCSV( std::string file_name  ) {
	if ( !_data.empty( ) ) {
		_width = 0;
		_height = 0;
		_data.clear( );
	}
	//ファイルの読み込み
	if ( file_name.find( ".csv" ) == std::string::npos  ) {
		file_name += ".csv";
	}
	file_name = "../resource2D/" + file_name;
	FILE* fp;
	fopen_s( &fp, file_name.c_str( ), "r" );
	if ( fp == NULL ) {
		return;
	}
    //csvファイルを1行ずつ読み込む
	char buf[ 2048 ];
	while ( fgets( buf, 2048, fp ) != NULL ) {
		std::string str = buf;
		while ( true ) {
			if ( _height == 0 ) {
				_width++;
			}
			std::string::size_type index = str.find( "," );
			if ( index == std::string::npos ) {
				_data.push_back( atoi( str.c_str( ) ) );
				break;
			}
			std::string substr = str.substr( 0, index );
			_data.push_back( atoi( substr.c_str( ) ) );
			str = str.substr( index + 1 );
		}
		_height++;
	}
}

void GroundMaker::save( ) {
	FILE* fp;
	fopen_s( &fp,"../resource2D/map.grd", "w" );
	fprintf( fp, "%d\n", _width );
	fprintf( fp, "%d\n", _height );
	for ( int i = 0; i < _width * _height; i++ ) {
		fprintf( fp, "%d\n", _data[ i ] );
	}
	fclose( fp );
}
