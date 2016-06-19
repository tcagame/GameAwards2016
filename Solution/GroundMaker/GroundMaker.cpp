#include "Framework.h"
#include "GroundMaker.h"
#include "ModelMake.h"
#include "Viewer.h"
#include "Ground.h"
#include "Binary.h"
#include <assert.h>

const int CSV_PLAIN    = 0;
const int CSV_DESERT   = 1;
const int CSV_MOUNTAIN = 2;
const int CSV_RIVER    = 3;

const GROUND_CHIP_TYPE CONVERT[ 4 ] = {
	GROUND_CHIP_TYPE_PLAIN    , // 0
	GROUND_CHIP_TYPE_DESERT   , // 1
	GROUND_CHIP_TYPE_MOUNTAIN , // 2
	GROUND_CHIP_TYPE_RIVER    , // 3
};

const int INPUT_X = 100;
const int INPUT_Y = 100;

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
		makeGroundModel( );
		mdlMake( );
		_state = STATE_SAVE;
		break;
	case STATE_SAVE:
		save( );
		_viewer->setModel( );
		_state = STATE_VIEWER;
		break;
	case STATE_VIEWER:
		viewer( );
		break;
	}
}

void GroundMaker::viewer( ) {
	_viewer->draw( );
}

bool GroundMaker::inputFileName( ) {
	FrameworkPtr fw = Framework::getInstance( );
	_file_name = fw->inputString( INPUT_X, INPUT_Y );
	if ( _file_name.empty( ) ) {
		fw->terminate( );
		return false;
	}
	return true;
}

void GroundMaker::loadToCSV( ) {
	//ファイルの読み込み
	std::string file = _file_name + ".csv";
	FILE* fp;
	errno_t err = fopen_s( &fp, file.c_str( ), "r" );
	if ( err != 0 ) {
		assert( false );
		return;
	}
	
	char buf[ 2048 ];

    //　カウントする
	int width = 0;
	int height = 0;
	while ( fgets( buf, 2048, fp ) != NULL ) {
		int w = 0;
		std::string str = buf;
		while ( true ) {
			w++;
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
	int idx = 0;
	fseek( fp, 0, SEEK_SET );
	while ( fgets( buf, 2048, fp ) != NULL ) {
		std::string str = buf;
		while ( true ) {
			std::string::size_type index = str.find( "," );
			if ( index == std::string::npos ) {
				_ground->setType( idx % width, idx / width, CONVERT[ atoi( str.c_str( ) ) ] );
				idx++;
				break;
			}
			std::string substr = str.substr( 0, index );
			_ground->setType( idx % width, idx / width, CONVERT[ atoi( substr.c_str( ) ) ]  );
			idx++;
			str = str.substr( index + 1 );
		}
	}
}


void GroundMaker::makeGroundModel( ) {
	int model_chip_width  = _ground->getWidth( )  + 1;
	int model_chip_height = _ground->getHeight( ) + 1;

	_mountain_map.clear( );
	_plain_map.clear( );
	_desert_map.clear( );
	_river_map.clear( );
	for ( int i = 0; i < model_chip_width; i++ ) {
		for ( int j = 0; j < model_chip_height; j++ ) {
			_mountain_map.push_back( makeModelChip( i, j, GROUND_CHIP_TYPE_MOUNTAIN ) );
			_plain_map.push_back   ( makeModelChip( i, j, GROUND_CHIP_TYPE_PLAIN    ) );
			_desert_map.push_back  ( makeModelChip( i, j, GROUND_CHIP_TYPE_DESERT   ) );
			_river_map.push_back   ( makeModelChip( i, j, GROUND_CHIP_TYPE_RIVER    ) );
		}
	}
}

unsigned char GroundMaker::makeModelChip( int mx, int my, GROUND_CHIP_TYPE type ) {
	unsigned char num = 0;
	for ( int i = 0; i < 4; i++ ) {
		num <<= 1;

		int x = mx - 1 + i % 2;
		int y = my - 1 + i / 2;
		GROUND_CHIP_TYPE type = _ground->getType( x, y );
		if ( _ground->getType( x, y ) == type ) {
			num += 1;
		}
	}

	return num;
}

void GroundMaker::mdlMake( ) {
	_model_make->setModel( );
}

void GroundMaker::save( ) {
	// grd保存
	BinaryPtr binary = _ground->makeBinary( );
	std::string file = _file_name + ".grd";
	FrameworkPtr fw = Framework::getInstance( );
	fw->saveBinary( file.c_str( ), binary );

	// mdl保存
	_model_make->saveModel( ); 
}

MAP_TYPE GroundMaker::getMapType( int mx, int my, GROUND_CHIP_TYPE type ) {
	int idx = my * getMapWidth( ) + mx;
	MAP_TYPE result;
	switch ( type ) {
	case GROUND_CHIP_TYPE_PLAIN:
		result = _plain_map[ idx ];
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
	return _ground->getWidth( ) + 1;
}

int GroundMaker::getMapHeight( ) {
	return _ground->getHeight( ) + 1;
}
