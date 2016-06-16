#include "Framework.h"
#include "GroundMaker.h"
#include "ModelMake.h"
#include "Viewer.h"
#include "Ground.h"
#include "DxLib.h"
#include <assert.h>

const int INPUT_X = 100;
const int INPUT_Y = 100;
const int MAX_STRING = 1024;
const char DIRECTORY[] = "../resource2D/";

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
	_state = STATE_INPUT;
	_model_make = ModelMakePtr( new ModelMake( ) );
	_viewer = ViewerPtr( new Viewer( ) );
}

GroundMaker::~GroundMaker( ) {
}

void GroundMaker::update( ) {
	switch ( _state ) {
		case STATE_INPUT:
		if ( inputFileName( ) ) {
			_state = STATE_LOAD;
		}
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
		_viewer->setModel( );
		_state = STATE_END;
		break;
	case STATE_END:
		_viewer->draw( );
		break;
	}
}

bool GroundMaker::inputFileName( ) {
	char buf[ MAX_STRING ];
	bool result = ( KeyInputString( INPUT_X, INPUT_Y, MAX_STRING, buf, TRUE ) == TRUE );
	if ( result ) {
		_file_name = buf;
		_file_name = DIRECTORY + _file_name;
		if ( _file_name.find( ".csv" ) == std::string::npos ) {
			_file_name += ".csv";
		}
	}
	return result;
}

void GroundMaker::loadToCSV( ) {
	//ファイルの読み込み
	if ( _file_name.find( ".csv" ) == std::string::npos  ) {
		_file_name += ".csv";
	}
	_file_name = DIRECTORY + _file_name;
	FILE* fp;
	errno_t err = fopen_s( &fp, _file_name.c_str( ), "r" );
	if ( err != 0 ) {
		const bool NotFile = !( err != 0 );
		assert( NotFile );
		return;
	}

    //　カウントする
	int width = 0;
	int height = 0;
	char buf[ 2048 ];
	while ( fgets( buf, 2048, fp ) != NULL ) {
		int w = 0;
		std::string str = buf;
		while ( true ) {
			width++;
			std::string::size_type index = str.find( "," );
			if ( index == std::string::npos ) {
				break;
			}
			std::string substr = str.substr( 0, index );
			str = str.substr( index + 1 );
		}

		if ( height == 0 ) {
			width = w;
		}
		assert( width == w );

		height++;
	}

	_ground = GroundPtr( new Ground( width, height ) );

	// 読み込む
	char buf[ 2048 ];
	int idx = 0;
	while ( fgets( buf, 2048, fp ) != NULL ) {
		int x = 0;
		std::string str = buf;
		while ( true ) {
			std::string::size_type index = str.find( "," );
			if ( index == std::string::npos ) {
				setGroundTypeFromCSV( idx, str.c_str( ) );
				break;
			}
			setGroundTypeFromCSV( idx, str.c_str( ) );
			std::string substr = str.substr( 0, index );
			str = str.substr( index + 1 );
		}
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
}

void GroundMaker::save( ) {
	FILE* fp;
	std::string file_name = DIRECTORY;
	file_name += "map.grd";
	fopen_s( &fp, file_name.c_str( ), "w" );
	fprintf( fp, "%d\n", _width );
	fprintf( fp, "%d\n", _height );
	for ( int i = 0; i < _width * _height; i++ ) {
		fprintf( fp, "%d\n", _data[ i ] );
	}
	fclose( fp );
	_model_make->saveModel( ); 
}

void GroundMaker::makeMountain( int mx, int my ) {
	int num = 0;
	for ( int i = 0; i < 4; i++ ) {
		num = num << 1;
		GROUND_CHIP_TYPE chip = getType( mx + DIR[ i ].first, my + DIR[ i ].second );
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
		GROUND_CHIP_TYPE chip = getType( mx + DIR[ i ].first, my + DIR[ i ].second );
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
		GROUND_CHIP_TYPE chip = getType( mx + DIR[ i ].first, my + DIR[ i ].second );
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
		GROUND_CHIP_TYPE chip = getType( mx + DIR[ i ].first, my + DIR[ i ].second );
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