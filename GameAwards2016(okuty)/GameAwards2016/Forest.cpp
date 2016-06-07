#include "Forest.h"
#include "App.h"
#include "Map.h"

static const int WIDTH = 3;
static const int HEIGHT = 3;
static const int HP = 1000;

Forest::Forest( MapPtr map ) :
Material( map, WIDTH, HEIGHT ) {
	_hp = HP;
	erased = false;
	_target_flag = false;
}

Forest::~Forest( ) {
}

void Forest::update( ) {

}

bool Forest::install( const Coord& pos, unsigned char value ) {
	return Material::install( pos, CHIP_TYPE_FOREST, value );
}

bool Forest::isTarget( ) {
	return _target_flag;
}

void Forest::setTargetFlag( bool flag ) {
	_target_flag = flag;
}

void Forest::attack( int damage ) {
	_hp -= damage;
	isExist( );
}

void Forest::erase( ) {
	if ( erased ) {
		return;
	}
	AppPtr app = App::getTask( );
	MapPtr map = app->getMap( );
	Map::Chip chip;
	chip.type = CHIP_TYPE_NONE;
	chip.value = 0;
	for ( int i = 0;i < HEIGHT; i++ ) {
		for ( int j = 0; j < WIDTH; j++ ) {
			Coord pos = Coord( getCoord( ).x + j, getCoord( ).y + i );
			map->setChip( pos, chip );
		}
	}
	erased = true;
}

bool Forest::isExist( ) {
	if ( _hp <= 0 ) {
		erase( );
		return false;
	}
	return true;
}

