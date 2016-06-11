#include "MapMaker.h"
#include "GroundMaker.h"
//#include "ModelMaker.h"

const std::pair< int, int > DIR[ 4 ] = {
	std::make_pair( 1, 1 ),
	std::make_pair( 0, 1 ),
	std::make_pair( 1, 0 ),
	std::make_pair( 0, 0 )
};

MapMaker::MapMaker( ) {
	_ground_maker = GroundMakerPtr( new GroundMaker( ) );
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
	makePlane( );
	makeDesert( );
	makeMountain( );
	makeRiver( );
}

void MapMaker::save( ) {
	_ground_maker->save( );
}

void MapMaker::makeMountain( ) {
	for ( int i = 0; i < _map_height; i++ ) {
		for ( int j = 0; j < _map_width; j++ ) {
			int num = 0;
			for ( int k = 0; k < 4; k++ ) {
				num = num << 1;
				GROUND_CHIP_TYPE chip = _ground_maker->getGroundChip( j + DIR[ k ].first, i + DIR[ k ].second );
				if ( chip == GROUND_CHIP_TYPE_MOUNTAIN ) {
					num += 1;
				}
			}
			_mountain_map.push_back( num );
		}
	}
}

void MapMaker::makeRiver( ) {
	for ( int i = 0; i < _map_height; i++ ) {
		for ( int j = 0; j < _map_width; j++ ) {
			int num = 0;
			for ( int k = 0; k < 4; k++ ) {
				num = num << 1;
				GROUND_CHIP_TYPE chip = _ground_maker->getGroundChip( j + DIR[ k ].first, i + DIR[ k ].second );
				if ( chip == GROUND_CHIP_TYPE_RIVER ) {
					num += 1;
				}
			}
			_river_map.push_back( num );
		}
	}
}

void MapMaker::makePlane( ) {
	for ( int i = 0; i < _map_height; i++ ) {
		for ( int j = 0; j < _map_width; j++ ) {
			int num = 0;
			for ( int k = 0; k < 4; k++ ) {
				num = num << 1;
				GROUND_CHIP_TYPE chip = _ground_maker->getGroundChip( j + DIR[ k ].first, i + DIR[ k ].second );
				if ( chip == GROUND_CHIP_TYPE_PLAIN ) {
					num += 1;
				}
			}
			_plane_map.push_back( num );
		}
	}
}

void MapMaker::makeDesert( ) {
	for ( int i = 0; i < _map_height; i++ ) {
		for ( int j = 0; j < _map_width; j++ ) {
			int num = 0;
			for ( int k = 0; k < 4; k++ ) {
				num = num << 1;
				GROUND_CHIP_TYPE chip = _ground_maker->getGroundChip( j + DIR[ k ].first, i + DIR[ k ].second );
				if ( chip == GROUND_CHIP_TYPE_DESERT ) {
					num += 1;
				}
			}
			_desert_map.push_back( num );
		}
	}
}