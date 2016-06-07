#include "Miner.h"
#include "App.h"
#include "Map.h"
#include "GoldMines.h"
#include "GoldMine.h"

static const int POWER = 1000;

static const Coord FACTORY_DIFF = Coord( 1, 3 );

Miner::Miner( const std::vector< Coord >& root, const Coord& target_pos ) :
Character( root, target_pos ) {
	_gold = 0;
	_pop_point = root.front( );
}

Miner::~Miner( ) {
}

void Miner::action( ) {
	AppPtr app = App::getTask( );
	MapPtr map = app->getMap( );
	Map::Chip chip = map->getChip( getCoord( ) );
	if ( chip.type == CHIP_TYPE_GOLD_MINE && _gold == 0 ) {
		GoldMinesPtr gold_mines = app->getGoldMines( );
		GoldMinePtr gold_mine = gold_mines->get( chip.value );
		_gold = gold_mine->getGold( POWER );
	}
	if ( getCoord( ).getIdx( ) == _pop_point.getIdx( ) ) {
		app->addGold( _gold );
		_gold = 0;
	}
}