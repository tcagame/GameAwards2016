#include "Framework.h"
#include "Model.h"
#include "GroundMaker.h"
#include "Ground.h"
#include "Binary.h"
#include <assert.h>
#include "DxLib.h"

const int CHIP_SIZE = 1;
const int MODEL_DIFF = CHIP_SIZE / 2;

const int CSV_PLAIN    = 0;
const int CSV_DESERT   = 1;
const int CSV_MOUNTAIN = 2;
const int CSV_RIVER    = 3;

const GROUND_CHIP_TYPE CONVERT[ ] = {
	GROUND_CHIP_TYPE_PLAIN    , // 0
	GROUND_CHIP_TYPE_DESERT   , // 1
	GROUND_CHIP_TYPE_MOUNTAIN , // 2
	GROUND_CHIP_TYPE_RIVER    , // 3
	GROUND_CHIP_TYPE_TREE     , // 4
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
}

GroundMaker::~GroundMaker( ) {
}

void GroundMaker::update( ) {

	while ( true ) {
		if ( !inputFileName( ) ) {
			break;
		}

		if ( !makeGround( ) )  {
			break;
		}

		if ( !makeModel( ) ) {
			break;
		}

		break;
	}
	
	FrameworkPtr fw = Framework::getInstance( );
	fw->terminate( );
}

bool GroundMaker::inputFileName( ) {
	FrameworkPtr fw = Framework::getInstance( );
	_file_name = fw->inputString( INPUT_X, INPUT_Y );
	if ( _file_name.empty( ) ) {
		return false;
	}
	return true;
}

bool GroundMaker::makeGround( ) {
	//ファイルの読み込み
	std::string file = _file_name + ".csv";
	FILE* fp;
	errno_t err = fopen_s( &fp, file.c_str( ), "r" );
	if ( err != 0 ) {
		return false;
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
		if ( width != w ) {
			return false;
		}

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

	// 間引きする
	_ground->toThinningTrees( );

	// grd保存
	BinaryPtr binary = _ground->makeBinary( );
	std::string file_grd = _file_name + ".grd";
	FrameworkPtr fw = Framework::getInstance( );
	fw->saveBinary( file_grd, binary );
	return true;
}

bool GroundMaker::makeModel( ) {
	//モデル読み込み

	ModelPtr model_moutain[ 16 ];
	ModelPtr model_river[ 16 ];
	ModelPtr model_desert[ 16 ];
	ModelPtr model_plain[ 16 ];

	for ( int i = 0; i < 16; i++ ) {
		model_moutain[ i ] = ModelPtr( new Model( ) );
		model_river[ i ] = ModelPtr( new Model( ) );
		model_desert[ i ] = ModelPtr( new Model( ) );
		model_plain[ i ] = ModelPtr( new Model( ) );
	}

	for( int i = 1; i < 16; i++ ) {
		model_moutain[ i ]->load( getModelFile( i, GROUND_CHIP_TYPE_MOUNTAIN ) );
		model_river[ i ]->load( getModelFile( i, GROUND_CHIP_TYPE_RIVER ) );
		model_desert[ i ]->load( getModelFile( i, GROUND_CHIP_TYPE_DESERT ) );
		model_plain[ i ]->load( getModelFile( i, GROUND_CHIP_TYPE_PLAIN ) );
	}

	//各地形モデルの配置
	int model_chip_width  = _ground->getWidth( )  + 1;
	int model_chip_height = _ground->getHeight( ) + 1;
	std::vector< int > plain_map;
	std::vector< int > desert_map;
	std::vector< int > mountain_map;
	std::vector< int > river_map;
	for ( int j = 0; j < model_chip_height; j++ ) {
		for ( int i = 0; i < model_chip_width; i++ ) {
			mountain_map.push_back( makeModelChip( i, j, GROUND_CHIP_TYPE_MOUNTAIN ) );
			plain_map.push_back   ( makeModelChip( i, j, GROUND_CHIP_TYPE_PLAIN    ) );
			desert_map.push_back  ( makeModelChip( i, j, GROUND_CHIP_TYPE_DESERT   ) );
			river_map.push_back   ( makeModelChip( i, j, GROUND_CHIP_TYPE_RIVER    ) );
		}
	}
	
	//地形モデル作成
	ModelPtr model_ground = ModelPtr( new Model( ) );
	for ( int j = 0; j < model_chip_height; j++ ) {
		for ( int i = 0; i < model_chip_width; i++ ) {
			ModelPtr model = ModelPtr( new Model( ) );
			int chip = plain_map[ i + j * model_chip_width ];
			if ( chip > 0 ) {
				model->mergeModel( model_plain[ chip ] );
			}
			chip = desert_map[ i + j * model_chip_width ];
			if ( chip > 0 ) {
				model->mergeModel( model_desert[ chip ] );
			}
			chip = mountain_map[ i + j * model_chip_width ];
			if ( chip > 0 ) {
				model->mergeModel( model_moutain[ chip ] );
			}
			chip = river_map[ i + j * model_chip_width ];
			if ( chip > 0 ) {
				model->mergeModel( model_river[ chip ] );
			}
			//1チップモデルの配置
			Matrix mat = Matrix::makeTransformTranslation( Vector( i * CHIP_SIZE, j * CHIP_SIZE ) );
			model->multiply( mat );
			//1チップモデルの追加
			model_ground->mergeModel( model );

			ScreenFlip( );
			ClearDrawScreen( );
			int percent = ( j * model_chip_width + i ) * 100 / ( model_chip_width * model_chip_height );
			DrawFormatString( 0, 0, GetColor( 255, 255, 255 ), "%d %%", percent );
		}
	}
	model_ground->save( "Map.mdl" );

	return true;
}

unsigned char GroundMaker::makeModelChip( int mx, int my, GROUND_CHIP_TYPE type ) {
	unsigned char num = 0;
	for ( int i = 0; i < 4; i++ ) {
		num <<= 1;

		int x = mx - i % 2;
		int y = my - i / 2;
		GROUND_CHIP_TYPE chip_type = _ground->getTypeTerrain( x, y );
		if ( chip_type == type ) {
			num += 1;
		}
	}

	return num;
}

int GroundMaker::getMapWidth( ) {
	return _ground->getWidth( ) + 1;
}

int GroundMaker::getMapHeight( ) {
	return _ground->getHeight( ) + 1;
}

std::string GroundMaker::getModelFile( int idx, unsigned char type ) {
	std::string filename;
	switch( type ){
	case GROUND_CHIP_TYPE_PLAIN:
		filename += "plain_";
		break;
	case GROUND_CHIP_TYPE_TREE: 
	case GROUND_CHIP_TYPE_DESERT: 
		filename += "desert_";
		break;
	case GROUND_CHIP_TYPE_MOUNTAIN:
		filename += "mountain_";
		break;
	case GROUND_CHIP_TYPE_RIVER:
		filename += "river_";
		break;
	default:
		break;
	}
	switch( idx ) {
	case MAP_TYPE_FFFT:
		filename += "01.mdl";
		break;
	case MAP_TYPE_FFTF:
		filename += "02.mdl";
		break;
	case MAP_TYPE_FFTT:
		filename += "03.mdl";
		break;
	case MAP_TYPE_FTFF:
		filename += "04.mdl";
		break;
	case MAP_TYPE_FTFT:
		filename += "05.mdl";
		break;
	case MAP_TYPE_FTTF:
		filename += "06.mdl";
		break;
	case MAP_TYPE_FTTT:
		filename += "07.mdl";
		break;
	case MAP_TYPE_TFFF:
		filename += "08.mdl";
		break;
	case MAP_TYPE_TFFT:
		filename += "09.mdl";
		break;
	case MAP_TYPE_TFTF:
		filename += "10.mdl";
		break;
	case MAP_TYPE_TFTT:
		filename += "11.mdl";
		break;
	case MAP_TYPE_TTFF:
		filename += "12.mdl";
		break;
	case MAP_TYPE_TTFT:
		filename += "13.mdl";
		break;
	case MAP_TYPE_TTTF:
		filename += "14.mdl";
		break;
	case MAP_TYPE_TTTT:
		filename += "15.mdl";
		break;
	default:
		break;
	} 
	return filename;
}