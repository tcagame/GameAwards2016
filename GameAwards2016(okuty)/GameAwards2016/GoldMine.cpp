#include "GoldMine.h"

static const int WIDTH = 3;
static const int HEIGHT = 3;
static const int GOLD = 1000;

GoldMine::GoldMine( MapPtr map ) :
Material( map, WIDTH, HEIGHT ) {
	_gold = GOLD;
	_target_flag = false;
}

GoldMine::~GoldMine( ) {
}

void GoldMine::update( ) {
}

bool GoldMine::install( const Coord& pos, unsigned char value ) {
	return Material::install( pos, CHIP_TYPE_GOLD_MINE, value );
}

int GoldMine::getGold( int power ) {
	if ( !isExist( ) ) {
		return 0;
	}
	int result = power;
	_gold -= power;
	if ( _gold < 0 ) {
		result -= _gold;
		_gold = 0;
	}
	return result;
}

bool GoldMine::isExist( ) const {
	bool result = ( _gold > 0 );
	return result;
}

bool GoldMine::isTarget( ) const {
	return _target_flag;
}

void GoldMine::setTargetFlag( bool flag ) {
	_target_flag = flag;
}