#include "ModelManager.h"
#include "GroundChip.h"
#include "MapChip.h"
#include "MapMaker.h"
#include "FileManager.h"
#include "Model.h"
#include "DxLib.h"

const int CHIP_SIZE = 10;
const char * FILE_NAME = "model/texture.png";

ModelManager::ModelManager( MapMakerPtr map_maker, FileManagerPtr file_manager, ModelPtr model ) {
	_map_maker = map_maker;
	_file_manager = file_manager;
	_model = model;
	loadModel( );
	setDrawModel( );
}

ModelManager::ModelManager() {
}


ModelManager::~ModelManager() {
}


void ModelManager::loadModel( ){
	int width = _map_maker->getWidth( );
	int height = _map_maker->getHeight( );

	for ( int i = 0; i < width; i++ ) {
		for ( int j = 0; j < height; j++ ) {
			loadPlainModel( i, j );
			loadDesertModel( i, j );
			loadMountainModel( i, j );
			loadRiverModel( i, j );
		}
	}
}

void ModelManager::setDrawModel( ) {
	int polygon_num = _file_manager->getPolygonNum( );
	int point_num = polygon_num * 3;
	_model->alloc( polygon_num );
	int texture_id = LoadGraph( FILE_NAME );
	_model->setTexture( texture_id );
	for ( int i = 0; i < point_num; i++ ) {
		Model::VERTEX vertex = _file_manager->getVERTEX( i );
		_model->set( i, vertex );
	}
}

void ModelManager::loadMountainModel( int mx, int my ) {
	int idx = _map_maker->getMapType( mx, my, GROUND_CHIP_TYPE_MOUNTAIN );
	if ( idx == MAP_TYPE_FFFF ) {
		return;
	}
	int sx = mx * CHIP_SIZE;
	int sz = -my * CHIP_SIZE;
	std::string name = getModelFile( idx, GROUND_CHIP_TYPE_MOUNTAIN );
	_file_manager->createModelData( sx, sz, name.c_str( ) );
}

  
void ModelManager::loadPlainModel( int mx, int my ) {
	int idx = _map_maker->getMapType( mx, my, GROUND_CHIP_TYPE_PLAIN );
	if ( idx == MAP_TYPE_FFFF ) {
		return;
	}
	int sx = mx * CHIP_SIZE;
	int sy = -my * CHIP_SIZE;
	std::string name = getModelFile( idx, GROUND_CHIP_TYPE_PLAIN );
	_file_manager->createModelData( sx, sy, name.c_str( ) );
}

void ModelManager::loadDesertModel( int mx, int my ) {
	int idx = _map_maker->getMapType( mx, my, GROUND_CHIP_TYPE_DESERT );
	if ( idx == MAP_TYPE_FFFF ) {
		return;
	}
	int sx = mx * CHIP_SIZE;
	int sy = -my * CHIP_SIZE;
	std::string name = getModelFile( idx, GROUND_CHIP_TYPE_DESERT );
	_file_manager->createModelData( sx, sy, name.c_str( ) );
}

void ModelManager::loadRiverModel( int mx, int my ) {
	int idx = _map_maker->getMapType( mx, my, GROUND_CHIP_TYPE_RIVER );
	if ( idx == MAP_TYPE_FFFF ) {
		return;
	}
	int sx = mx * CHIP_SIZE;
	int sy = -my * CHIP_SIZE;
	std::string name = getModelFile( idx, GROUND_CHIP_TYPE_RIVER );
	_file_manager->createModelData( sx, sy, name.c_str( ) );
}



std::string ModelManager::getModelFile( int idx, unsigned char type ) {
	std::string filename;
	switch( type ){
	case GROUND_CHIP_TYPE_PLAIN:
		filename = "p_";
		break;
	case GROUND_CHIP_TYPE_DESERT: 
		filename = "d_";
		break;
	case GROUND_CHIP_TYPE_MOUNTAIN:
		filename = "g_";
		break;
	case GROUND_CHIP_TYPE_RIVER:
		filename = "water_";
		break;
	default:
		break;
	}
	switch( idx ) {
	case MAP_TYPE_FFFF:
		return "none.x";
	case MAP_TYPE_FFFT:
		filename += "01.x";
		break;
	case MAP_TYPE_FFTF:
		filename += "02.x";
		break;
	case MAP_TYPE_FFTT:
		filename += "03.x";
		break;
	case MAP_TYPE_FTFF:
		filename += "04.x";
		break;
	case MAP_TYPE_FTFT:
		filename += "05.x";
		break;
	case MAP_TYPE_FTTF:
		filename += "06.x";
		break;
	case MAP_TYPE_FTTT:
		filename += "07.x";
		break;
	case MAP_TYPE_TFFF:
		filename += "08.x";
		break;
	case MAP_TYPE_TFFT:
		filename += "09.x";
		break;
	case MAP_TYPE_TFTF:
		filename += "10.x";
		break;
	case MAP_TYPE_TFTT:
		filename += "11.x";
		break;
	case MAP_TYPE_TTFF:
		filename += "12.x";
		break;
	case MAP_TYPE_TTFT:
		filename += "13.x";
		break;
	case MAP_TYPE_TTTF:
		filename += "14.x";
		break;
	case MAP_TYPE_TTTT:
		filename += "15.x";
		break;
	default:
		break;
	} 
	return filename;
}