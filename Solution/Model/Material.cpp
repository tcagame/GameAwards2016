#include "Material.h"
#include "Map.h"

Material::Material( MapPtr map, const int width, const int height ) :
_width( width ),
_height( height ),
_map( map ){
}

Material::~Material( ) {
}

bool Material::install( const Coord& coord, CHIP_TYPE type, int value ) {
	if ( coord.getIdx( ) == -1 ) {
		return false;
	}

	for ( int i = 0; i < _width; i++ ) {
		for ( int j = 0; j < _height; j++ ) {
			Coord search_coord = coord;
			search_coord.x += i;
			search_coord.y += j;
			if ( search_coord.getIdx( ) == -1 ) {
				return false;
			}
			CHIP_TYPE type = _map->getChip( search_coord ).type;
			if ( type != CHIP_TYPE_NONE ) {
				return false;
			}
		}
	}

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