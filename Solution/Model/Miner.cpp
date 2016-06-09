#include "Miner.h"
#include "Map.h"
#include "GoldMine.h"

static const int POWER = 1000;

static const Coord FACTORY_DIFF = Coord( 1, 3 );

Miner::Miner( const std::vector< Coord >& root, GoldMinePtr goldmine ) :
Character( root ) {
	_gold = 0;
	_pop_point = root.front( );
	_goldmine = goldmine;
}

Miner::~Miner( ) {
}

bool Miner::existMaterial( ) {
	return _goldmine->isExist( );
}

void Miner::action( ) {
	if ( _goldmine->getCoord( ).getIdx( ) == getCoord( ).getIdx( ) && _gold == 0 ) {
		_gold = _goldmine->getGold( POWER );
	}
	if ( getCoord( ).getIdx( ) == _pop_point.getIdx( ) ) {
		//addGold( _gold );
		_gold = 0;
	}
}