#include "MapMaker.h"
#include "GroundMaker.h"

const std::pair< int, int > DIR[ 4 ] = {
	std::make_pair( 1, 1 ),
	std::make_pair( 0, 1 ),
	std::make_pair( 1, 0 ),
	std::make_pair( 0, 0 )
};

MapMaker::MapMaker( ) {
	_ground_maker = GroundMakerPtr( new GroundMaker( ) );
	putFileName( );
	load( );
	mapMake( );
	save( );
}

MapMaker::~MapMaker( ) {
}

void MapMaker::putFileName( ) {
	_file_name = "map";
}

void MapMaker::load( ){
	_ground_maker->loadToCSV( _file_name );
	_map_height = _ground_maker->getHeight( ) -1;
	_map_width = _ground_maker->getWidth( ) -1;
}

void MapMaker::mapMake( ) {
	for ( int i = 0; i < _map_height; i++ ) {
		for ( int j = 0; j < _map_width; j++ ) {
			makePlane( j, i );
			makeDesert( j, i );
			makeMountain( j, i );
			makeRiver( j, i );
		}
	}
}

void MapMaker::save( ) {
	_ground_maker->save( );
	
}

void MapMaker::makeMountain( int mx, int my ) {
	int num = 0;
	for ( int i = 0; i < 4; i++ ) {
		num = num << 1;
		GROUND_CHIP_TYPE chip = _ground_maker->getGroundChip( mx + DIR[ i ].first, my + DIR[ i ].second );
		if ( chip == GROUND_CHIP_TYPE_MOUNTAIN ) {
			num += 1;
		}
	}
	_mountain_map.push_back( num );
}

void MapMaker::makeRiver( int mx, int my ) {
	int num = 0;
	for ( int i = 0; i < 4; i++ ) {
		num = num << 1;
		GROUND_CHIP_TYPE chip = _ground_maker->getGroundChip( mx + DIR[ i ].first, my + DIR[ i ].second );
		if ( chip == GROUND_CHIP_TYPE_RIVER ) {
			num += 1;
		}
	}
	_river_map.push_back( num );
}

void MapMaker::makePlane( int mx, int my ) {
	int num = 0;
	for ( int i = 0; i < 4; i++ ) {
		num = num << 1;
		GROUND_CHIP_TYPE chip = _ground_maker->getGroundChip( mx + DIR[ i ].first, my + DIR[ i ].second );
		if ( chip == GROUND_CHIP_TYPE_PLAIN ) {
			num += 1;
		}
	}
	_plane_map.push_back( num );
}

void MapMaker::makeDesert( int mx, int my ) {
	int num = 0;
	for ( int i = 0; i < 4; i++ ) {
		num = num << 1;
		GROUND_CHIP_TYPE chip = _ground_maker->getGroundChip( mx + DIR[ i ].first, my + DIR[ i ].second );
		if ( chip == GROUND_CHIP_TYPE_DESERT ) {
			num += 1;
		}
	}
	_desert_map.push_back( num );
}

int MapMaker::getWidth( ) const {
	return _map_width;
}

int MapMaker::getHeight( ) const {
	return _map_height;
}

MAP_TYPE MapMaker::getMapType( int mx, int my, GROUND_CHIP_TYPE type ) const {
	MAP_TYPE chip;
	int idx = my * _map_width + mx;
	switch ( type ) {
		case GROUND_CHIP_TYPE_PLAIN:
			chip = _plane_map[ idx ];
			break;
		case GROUND_CHIP_TYPE_DESERT:
			chip = _desert_map[ idx ];
			break;
		case GROUND_CHIP_TYPE_MOUNTAIN:
			chip = _mountain_map[ idx ];
			break;
		case GROUND_CHIP_TYPE_RIVER:
			chip = _river_map[ idx ];
			break;
	}
	return chip;
}