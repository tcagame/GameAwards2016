#include "Facility.h"
#include "Object.h"
#include "Map.h"
#include "App.h"
#include "Map.h"

Facility::Facility( MapPtr map, int width, int height ) :
_width( width ),
_height( height ), 
_map( map ) {
	_connect_coord_in = Coord( -1, -1 );
	_connect_coord_out = Coord( -1, -1 );
}


Facility::~Facility( ) {

}

// Facility
Coord Facility::getLineOutCoord( ) const {
	return _connect_coord_out;
}

Coord Facility::getLineInCoord( ) const {
	return _connect_coord_in;
}

bool Facility::install( const Coord& coord, CHIP_TYPE type, int value ) {
	const int RANGE = 2;

	// マップ範囲外か調べる
	if ( coord.x - RANGE < 0 ||
		 coord.y - RANGE < 0 ||
		 coord.x + RANGE + _width  >= COORD_WIDTH ||
		 coord.y + RANGE + _height >= COORD_HEIGHT ) {
		return false;
	}

	for ( int i = -RANGE; i < _width + RANGE; i++ ) {
		for ( int j = -RANGE; j < _height + RANGE; j++ ) {
			Coord search_coord = coord;
			search_coord.x += i;
			search_coord.y += j;

			CHIP_TYPE type = _map->getChip( search_coord ).type;
			
			// レッドゾーンを調べる
			if ( i > -RANGE && i < _width + RANGE - 1 &&
				 j > -RANGE && j < _height + RANGE - 1 ) {
				if ( type == CHIP_TYPE_LINE ) {
					return false;
				}
			}

			//変更前 if ( type == CHIP_TYPE_CHARGER || type == CHIP_TYPE_POWERPLANT || type == CHIP_TYPE_FACTORY ) {
			if ( type != CHIP_TYPE_NONE ) {
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
			chip.type = type;
			chip.value = value;
			_map->setChip( install_coord, chip );
		}
	}
	setCoord( coord );
	return true;
}

bool Facility::checkConnectLineCoord( ) {
	if ( _connect_coord_out.getIdx( ) >= 0 ) {
		return false;
	}
	return true;
}

void Facility::setConnectLineCoord( const Coord& coord ) {
	if ( _connect_coord_in.getIdx( ) < 0 ) {
		_connect_coord_in = coord;
	} else {
		_connect_coord_out = coord;
	}
}

void Facility::deleteConnectLineCoord( const Coord& coord ) {
	if ( coord.getIdx( ) != _connect_coord_in.getIdx( ) && coord.getIdx( ) != _connect_coord_out.getIdx( ) ) {
		return;
	}

	if ( _connect_coord_in.getIdx( ) == coord.getIdx( ) ) {
		_connect_coord_in = _connect_coord_out;
	}
	_connect_coord_out =  Coord( -1, -1 );
}
