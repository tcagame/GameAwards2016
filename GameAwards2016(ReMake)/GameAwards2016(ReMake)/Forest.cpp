#include "Forest.h"

static const int WIDTH = 3;
static const int HEIGHT = 3;

Forest::Forest( MapPtr map ) :
Material( map, WIDTH, HEIGHT ) {

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