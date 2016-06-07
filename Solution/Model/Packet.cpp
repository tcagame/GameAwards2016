#include "Packet.h"
#include "Coord.h"
#include "Ratio.h"
#include "Line.h"


Packet::Packet( const Coord& coord, const Ratio& x, const Ratio& y ) :
_ratio_coord( coord, x, y ),
_before_coord( coord ) {
	_is_center_chip = false;
}


Packet::~Packet( ) {
}

Coord Packet::getCoord( ) {
	return _ratio_coord.getCoord( );
}

Ratio Packet::getRatioX( ) {
	return _ratio_coord.getRatio( ).x;
}

Ratio Packet::getRatioY( ) {
	return _ratio_coord.getRatio( ).y;
}

void Packet::update( ) {
	if ( _next_dir == Line::DIR_NONE ) {
		return;
	}

	int ratio_x = _ratio_coord.getRatio( ).x.cal( Ratio::RATIO_ACCURACY );
	int ratio_y = _ratio_coord.getRatio( ).y.cal( Ratio::RATIO_ACCURACY );

	if ( ratio_x == Ratio::RATIO_ACCURACY / 2 || ratio_y == Ratio::RATIO_ACCURACY / 2 ) {
		_is_center_chip = true;
	}

	unsigned char start_dir = _line_dir & ~_next_dir;

	if ( start_dir == Line::DIR____R && !_is_center_chip ) {
		_ratio_coord.increase( Coord( -10, 0 ) );
	}
	if ( start_dir == Line::DIR__D__ && !_is_center_chip ) {
		_ratio_coord.increase( Coord( 0, -10 ) );
	}
	if ( start_dir == Line::DIR___L_ && !_is_center_chip ) {
		_ratio_coord.increase( Coord( 10, 0 ) );
	}
	if ( start_dir == Line::DIR_U___ && !_is_center_chip ) {
		_ratio_coord.increase( Coord( 0, 10 ) );
	}
	
	
	if ( !_is_center_chip ) {
		return;
	}
	switch( _next_dir ) {
	case Line::DIR_U___:
		_ratio_coord.increase( Coord( 0, -10 ) );
		break;
	case Line::DIR__D__:
		_ratio_coord.increase( Coord( 0, 10 ) );
		break;
	case Line::DIR___L_:
		_ratio_coord.increase( Coord( -10, 0 ) );
		break;
	case Line::DIR____R:
		_ratio_coord.increase( Coord( 10, 0 ) );
		break;
	default:
		break;
	}

}

bool Packet::isMoveNextCoord( ) {
	if ( _before_coord.getIdx( ) == _ratio_coord.getCoord( ).getIdx( ) ) {
		return false;
	}
	_is_center_chip = false;
	_before_coord = _ratio_coord.getCoord( );
	return true;
}

unsigned char Packet::getNextDir( ) {
	return _next_dir;
}

void Packet::setDir( unsigned char next_dir, unsigned char line_dir ) {
	_next_dir = next_dir;
	_line_dir = line_dir;
}