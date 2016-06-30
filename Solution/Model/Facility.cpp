#include "Facility.h"
#include "Object.h"
#include "Ground.h"
#include "Map.h"
#include "Map.h"

Facility::Facility( CHIP_TYPE type, int width, int height, MapPtr map, GroundConstPtr ground ) :
_chip_type( type ),
_width( width ),
_height( height ), 
_map( map ),
_ground( ground ) {
	_connect_fixation_left = Coord( -1, -1 );
	_connect_fixation_right = Coord( -1, -1 );
}


Facility::~Facility( ) {

}

Coord Facility::getLineFixationLeft( ) const {
	return _connect_fixation_left;
}

Coord Facility::getLineFixationRight( ) const {
	return _connect_fixation_right;
}


void Facility::destroy( const Coord& coord ) {
	Map::Chip chip;
	chip.type = CHIP_TYPE_NONE;
	chip.value = 0;
	for ( int i = 0; i < _width; i++ ) {
		for ( int j = 0; j < _height; j++ ) {
			Coord install_coord = coord;
			install_coord.x += i;
			install_coord.y += j;
			_map->setChip( install_coord, chip );
		}
	}
}

bool Facility::install( const Coord& coord, unsigned char value ) {
	const int RANGE = 2;

	// マップ範囲外か調べる
	if ( coord.x - RANGE < 0 ||
		 coord.y < 0 ||
		 coord.x + RANGE + _width  >= COORD_WIDTH ||
		 coord.y + _height >= COORD_HEIGHT ) {
		return false;
	}

	for ( int i = -RANGE; i < _width + RANGE; i++ ) {
		for ( int j = 0; j < _height; j++ ) {
			Coord search_coord = coord;
			search_coord.x += i;
			search_coord.y += j;

			CHIP_TYPE type = _map->getChip( search_coord ).type;
			GROUND_CHIP_TYPE ground_type = _ground->getType( search_coord.x, search_coord.y );
			
			// レッドゾーンを調べる
			if ( i > -RANGE && i < _width + RANGE - 1 &&
				 j > -RANGE && j < _height ) {
				if ( type == CHIP_TYPE_LINE ) {
					return false;
				}
			}

			if ( ground_type != GROUND_CHIP_TYPE_PLAIN && ground_type != GROUND_CHIP_TYPE_DESERT ) {
				return false;
			}

			if ( ( type & CHIP_TYPE_FACILITY ) != 0 ) {
				return false;
			}
		}
	}

	// マップに登録
	for ( int i = 0; i < _width; i++ ) {
		for ( int j = 0; j < _height; j++ ) {
			Coord install_coord = coord;
			install_coord.x += i;
			install_coord.y += j;
			Map::Chip chip;
			chip.type = _chip_type;
			chip.value = value;
			_map->setChip( install_coord, chip );

		}
	}

	//ライン接続固定位置登録
	_connect_fixation_left = Coord ( coord.x - 1, coord.y + ( ( _height - 1 ) / 2 ) );
	_connect_fixation_right = Coord ( coord.x + _width, coord.y + ( ( _height - 1 ) / 2 ) );
	setCoord( coord );
	return true;
}

Coord Facility::getExitCoord( const Coord& coord ) const {
	Coord exit_coord( -1, -1 );

	Coord left = _connect_fixation_left;
	left.x++;
	if ( coord.getIdx( ) == left.getIdx( ) ) {
		exit_coord = _connect_fixation_right;
	}
	Coord right = _connect_fixation_right;
	right.x--;
	if ( coord.getIdx( ) == right.getIdx( ) ) {
		exit_coord = _connect_fixation_left;
	} 
	return exit_coord;
}
