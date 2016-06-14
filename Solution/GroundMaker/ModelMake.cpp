#include "ModelMake.h"
#include "GroundChip.h"
#include "MapChip.h"
#include "ModelManager.h"
#include "GroundMaker.h"

const int CHIP_SIZE = 10;
const int TEXTURE_SIZE = 1024;
const int TEXTURE_CHIP_SIZE = TEXTURE_SIZE / 8;
const int MODEL_DIFF = CHIP_SIZE / 2;
const char * FILE_NAME = "../resource3D/model(dummy)/texture.png";

ModelMake::ModelMake( ) {
	_model_manager = ModelManagerPtr( new ModelManager( ) );
}

ModelMake::~ModelMake() {
}

void ModelMake::setModel( ){
	GroundMakerPtr ground_maker = GroundMaker::getTask( );
	int width = ground_maker->getMapWidth( );
	int height = ground_maker->getMapHeight( );
	for ( int i = 0; i < width; i++ ) {
		for ( int j = 0; j < height; j++ ) {
			setPlainModel( i, j );
			setDesertModel( i, j );
			setMountainModel( i, j );
			setRiverModel( i, j );
		}
	}
}

void ModelMake::saveModel( ) {
	_model_manager->saveModelData( "../resource3D/model(dummy)/Map.mdl" );
}

void ModelMake::setMountainModel( int mx, int my ) {
	GroundMakerPtr ground_maker = GroundMaker::getTask( );
	int idx = ground_maker->getMapType( mx, my, GROUND_CHIP_TYPE_MOUNTAIN );
	if ( idx == MAP_TYPE_FFFF ) {
		return;
	}
	int sx = mx * CHIP_SIZE;
	int sz = -my * CHIP_SIZE;
	std::string name = getModelFile( idx, GROUND_CHIP_TYPE_MOUNTAIN );
	_model_manager->loadModelData( name.c_str( ) );
	_model_manager->setModelPos( sx + MODEL_DIFF, sz - MODEL_DIFF );
}
 
void ModelMake::setPlainModel( int mx, int my ) {
	GroundMakerPtr ground_maker = GroundMaker::getTask( );
	int idx = ground_maker->getMapType( mx, my, GROUND_CHIP_TYPE_PLAIN );
	if ( idx == MAP_TYPE_FFFF ) {
		return;
	}
	int x = mx * CHIP_SIZE;
	int z = -my * CHIP_SIZE;
	unsigned char key = 0x01;
	for ( int i = 0 ;i < 4; i++ ) {
		if ( ( idx & key ) > 0 ) {
			int sx = x + i % 2 * ( CHIP_SIZE / 2 );
			int sz = z - i / 2 * ( CHIP_SIZE / 2 );
			int u = i % 2 * ( TEXTURE_CHIP_SIZE / 2 );
			int v = i / 2 * ( TEXTURE_CHIP_SIZE / 2 );
			setQuadranglePolygon( sx, sz, u, v );
		}
		key = key << 1;
	}
}

void ModelMake::setDesertModel( int mx, int my ) {
	GroundMakerPtr ground_maker = GroundMaker::getTask( );
	int idx = ground_maker->getMapType( mx, my, GROUND_CHIP_TYPE_DESERT );
	if ( idx == MAP_TYPE_FFFF ) {
		return;
	}
	int x = mx * CHIP_SIZE;
	int z = -my * CHIP_SIZE;
	int tx = idx % 8 * TEXTURE_CHIP_SIZE;
	int ty = ( GROUND_CHIP_TYPE_DESERT * 2 + idx / 8 ) * TEXTURE_CHIP_SIZE;
	unsigned char key = 0x01;
	for ( int i = 0 ;i < 4; i++ ) {
		if ( ( idx & key ) > 0 ) {
			int sx = x + i % 2 * ( CHIP_SIZE / 2 );
			int sz = z - i / 2 * ( CHIP_SIZE / 2 );
			int u = tx + i % 2 * ( TEXTURE_CHIP_SIZE / 2 );
			int v = ty + i / 2 * ( TEXTURE_CHIP_SIZE / 2 );
			setQuadranglePolygon( sx, sz, u, v );
		}
		key = key << 1;
	}
}

void ModelMake::setRiverModel( int mx, int my ) {
	GroundMakerPtr ground_maker = GroundMaker::getTask( );
	int idx = ground_maker->getMapType( mx, my, GROUND_CHIP_TYPE_RIVER );
	if ( idx == MAP_TYPE_FFFF ) {
		return;
	}
	int sx = mx * CHIP_SIZE;
	int sz = -my * CHIP_SIZE;
	std::string name = getModelFile( idx, GROUND_CHIP_TYPE_RIVER );
	_model_manager->loadModelData( name.c_str( ) );
	_model_manager->setModelPos( sx + MODEL_DIFF, sz - MODEL_DIFF );
}

std::string ModelMake::getModelFile( int idx, unsigned char type ) {
	std::string filename = "../resource3D/model(dummy)/";
	switch( type ){
	case GROUND_CHIP_TYPE_PLAIN:
		filename += "p_";
		break;
	case GROUND_CHIP_TYPE_DESERT: 
		filename += "d_";
		break;
	case GROUND_CHIP_TYPE_MOUNTAIN:
		filename += "g_";
		break;
	case GROUND_CHIP_TYPE_RIVER:
		filename += "water_";
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

void ModelMake::setQuadranglePolygon( int sx, int sz, int u, int v ) {
	Model::VERTEX vertex[ 4 ];
	Vector quad_point[ 4 ] = {
		Vector( 0, 0, 0 ),
		Vector( 1, 0, 0 ),
		Vector( 0, 0, -1 ),
		Vector( 1, 0, -1 ),
	};

	for ( int i = 0; i < 4; i++ ) {
		vertex[ i ].pos = Vector( ( double )sx, 0.0, ( double ) sz ) + quad_point[ i ] * ( CHIP_SIZE / 2 );
		vertex[ i ].u = ( double )( u + i % 2 * ( TEXTURE_CHIP_SIZE / 2 ) ) / TEXTURE_SIZE;
		vertex[ i ].v = ( double )( v + i / 2 * ( TEXTURE_CHIP_SIZE / 2 ) ) / TEXTURE_SIZE;
	}

	Model::VERTEX quad_vertex[ 6 ] = {
		vertex[ 0 ],
		vertex[ 1 ],
		vertex[ 3 ],
		vertex[ 0 ],
		vertex[ 3 ],
		vertex[ 2 ]
	};
	for ( int i = 0; i < 6; i++ ) {
		_model_manager->setVertex( quad_vertex[ i ] );
	}
}