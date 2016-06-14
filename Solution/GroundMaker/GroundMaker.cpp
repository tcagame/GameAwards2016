#include "Framework.h"
#include "GroundMaker.h"
#include "ModelMake.h"

const std::pair< int, int > DIR[ 4 ] = {
	std::make_pair( 1, 1 ),
	std::make_pair( 0, 1 ),
	std::make_pair( 1, 0 ),
	std::make_pair( 0, 0 )
};

GroundMakerPtr GroundMaker::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< GroundMaker >( fw->getTask( getTag( ) ) );
}

GroundMaker::GroundMaker( ) {
	_height = 0;
	_width = 0;
	_state = STATE_INPUT;
	_model_make = ModelMakePtr( new ModelMake( ) );
}

GroundMaker::~GroundMaker( ) {
}

void GroundMaker::update( ) {
	switch ( _state ) {
		case STATE_INPUT:
		inputFileName( );
		_state = STATE_LOAD;
		break;
		case STATE_LOAD:
		loadToCSV( );
		_state = STATE_MAKE;
		break;
		case STATE_MAKE:
		mapMake( );
		mdlMake( );
		_state = STATE_SAVE;
		break;
		case STATE_SAVE:
		save( );
		break;
	}
}

void GroundMaker::inputFileName( ) {
	_file_name = "map";
}

void GroundMaker::loadToCSV( ) {
	if ( !_data.empty( ) ) {
		_width = 0;
		_height = 0;
		_data.clear( );
	}
	//ファイルの読み込み
	if ( _file_name.find( ".csv" ) == std::string::npos  ) {
		_file_name += ".csv";
	}
	_file_name = "../resource2D/" + _file_name;
	FILE* fp;
	fopen_s( &fp, _file_name.c_str( ), "r" );
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

void GroundMaker::mapMake( ) {
	_map_height = getHeight( ) -1;
	_map_width = getWidth( ) -1;
	for ( int i = 0; i < _map_height; i++ ) {
		for ( int j = 0; j < _map_width; j++ ) {
			makePlane( j, i );
			makeDesert( j, i );
			makeMountain( j, i );
			makeRiver( j, i );
		}
	}
}

void GroundMaker::mdlMake( ) {
	_model_make->setModel( );
	_model_make->saveModel( ); 
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

void GroundMaker::makeMountain( int mx, int my ) {
	int num = 0;
	for ( int i = 0; i < 4; i++ ) {
		num = num << 1;
		GROUND_CHIP_TYPE chip = getGroundChip( mx + DIR[ i ].first, my + DIR[ i ].second );
		if ( chip == GROUND_CHIP_TYPE_MOUNTAIN ) {
			num += 1;
		}
	}
	_mountain_map.push_back( num );
}

void GroundMaker::makeRiver( int mx, int my ) {
	int num = 0;
	for ( int i = 0; i < 4; i++ ) {
		num = num << 1;
		GROUND_CHIP_TYPE chip = getGroundChip( mx + DIR[ i ].first, my + DIR[ i ].second );
		if ( chip == GROUND_CHIP_TYPE_RIVER ) {
			num += 1;
		}
	}
	_river_map.push_back( num );
}

void GroundMaker::makePlane( int mx, int my ) {
	int num = 0;
	for ( int i = 0; i < 4; i++ ) {
		num = num << 1;
		GROUND_CHIP_TYPE chip = getGroundChip( mx + DIR[ i ].first, my + DIR[ i ].second );
		if ( chip == GROUND_CHIP_TYPE_PLAIN ) {
			num += 1;
		}
	}
	_plane_map.push_back( num );
}

void GroundMaker::makeDesert( int mx, int my ) {
	int num = 0;
	for ( int i = 0; i < 4; i++ ) {
		num = num << 1;
		GROUND_CHIP_TYPE chip = getGroundChip( mx + DIR[ i ].first, my + DIR[ i ].second );
		if ( chip == GROUND_CHIP_TYPE_DESERT ) {
			num += 1;
		}
	}
	_desert_map.push_back( num );
}

MAP_TYPE GroundMaker::getMapType( int mx, int my, GROUND_CHIP_TYPE type ) {
	int idx = my * _map_width + mx;
	MAP_TYPE result;
	switch ( type ) {
		case GROUND_CHIP_TYPE_PLAIN:
		result = _plane_map[ idx ];
		break;
		case GROUND_CHIP_TYPE_DESERT:
		result = _desert_map[ idx ];
		break;
		case GROUND_CHIP_TYPE_MOUNTAIN:
		result = _mountain_map[ idx ];
		break;
		case GROUND_CHIP_TYPE_RIVER:
		result = _river_map[ idx ];
		break;
	}
	return result;
}

int GroundMaker::getMapWidth( ) {
	return _map_width;
}

int GroundMaker::getMapHeight( ) {
	return _map_height;
}