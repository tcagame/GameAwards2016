#include "Pioneer.h"
#include "Forest.h"

static const int POWER = 1000;

static const Coord FACTORY_DIFF = Coord( 1, 3 );

Pioneer::Pioneer( const std::vector< Coord >& root, ForestPtr forest ) :
Character( root ) {
	_pop_point = root.front( );
	_is_attack = false;
	_forest = forest;
}

Pioneer::~Pioneer( ) {
}

bool Pioneer::existMaterial( ) {
	return _forest->isExist( );
}

void Pioneer::action( ) {
	if ( _forest->getCoord( ).getIdx( ) == getCoord( ).getIdx( ) && !_is_attack ) {
		_forest->attack( POWER );
		_is_attack = true;
	}
	if ( getCoord( ).getIdx( ) == _pop_point.getIdx( ) ) {
		_is_attack = false;
	}
}