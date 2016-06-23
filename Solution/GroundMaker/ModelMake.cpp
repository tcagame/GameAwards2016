#include "ModelMake.h"
#include "GroundChip.h"
#include "MapChip.h"
#include "Model.h"
#include "GroundMaker.h"

const int CHIP_SIZE = 10;
const int TEXTURE_SIZE = 1024;
const int TEXTURE_CHIP_SIZE = TEXTURE_SIZE / 8;
const int MODEL_DIFF = CHIP_SIZE / 2;

ModelMake::ModelMake( ) {
	allLoadModel( );
}

ModelMake::~ModelMake( ) {
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
	_model_ground->save( "Map.mdl" );
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
	_model_ground->load( name.c_str( ) );
	//_model_ground->setModelPos( sx + MODEL_DIFF, sz - MODEL_DIFF );
}
 
void ModelMake::setPlainModel( int mx, int my ) {
}

void ModelMake::setDesertModel( int mx, int my ) {
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
	_model_ground->load( name );
	//_model_ground->setModelPos( sx + MODEL_DIFF, sz - MODEL_DIFF );
}

std::string ModelMake::getModelFile( int idx, unsigned char type ) {
	std::string filename;
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

void ModelMake::allLoadModel( ) {
	for( int i = 0; i < 16; i++ ) {
		_model_moutain[ i ]->load( getModelFile( i, GROUND_CHIP_TYPE_MOUNTAIN ) );
		_model_river[ i ]->load( getModelFile( i, GROUND_CHIP_TYPE_RIVER ) );
		//_model_desert[ i ] = CreateDesertModel( i );
		//_model_plain[ i ] = CreatePlaneModel( i );
	}
}