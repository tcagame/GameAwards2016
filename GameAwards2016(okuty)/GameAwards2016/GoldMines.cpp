#include "GoldMines.h"
#include "GoldMine.h"

GoldMines::GoldMines( MapPtr map ) {
	for ( int i = 0; i < NUM; i++ ) {
		_array[ i ] = GoldMinePtr( new GoldMine( map ) );
	}
	_idx = 0;
}

GoldMines::~GoldMines( ) {
}

GoldMineConstPtr GoldMines::get( int idx ) const {
	return _array[ idx ];
}

int GoldMines::getSize( ) const {
	return _idx;
}

bool GoldMines::install( const Coord& pos ) {
	if ( _idx >= NUM ) {
		return false;
	}
	GoldMinePtr gold_mine = _array[ _idx ];
	if ( gold_mine->install( pos, _idx ) ) {
		_idx++;
		return true;
	}
	return false;
}