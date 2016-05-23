#include "Character.h"
#include "App.h"
#include "mathmatics.h"
#include "Map.h"
#include <array>
#include <queue>

Character::Character( const Coord& pos, const std::vector<Coord>& root ) {
	_speed = 1;
	_target_key = 0;
	_root = root;
	setCoord( pos );

	_time = 0;
}

Character::~Character( ) {
}

void Character::update( ) {
	move( );
	action( );
}

void Character::getRootPoint( ) {
	Coord pos = getCoord( );
	if ( ( int )_root.size( ) == 1 ) {
		return;
	}
	if ( _target_key < ( int )_root.size( ) - 1 ) {
		Coord target = _root[ _target_key ];
		if ( pos.getIdx( ) == target.getIdx( ) ) {
			_target_key++;
		}
	} else {
		_target_key = 0;
	}

	_target = Vector( _root[ _target_key ].x, _root[ _target_key ].y );
}

void Character::move( ) {
	if ( _time % 10 == 0 ) {
		getRootPoint( );
		_time = 0;
	}
	_time++;
	Vector dir = _target - Vector( getCoord( ).x, getCoord( ).y );
	dir = dirNomarize( dir );
	Coord pos = getCoord( );
	pos.x += ( int )( dir.x * _speed );
	pos.y += ( int )( dir.y * _speed );
	setCoord( pos );
}

Vector Character::dirNomarize( const Vector& dir ) {
	Vector result = dir.normalize( );
	if ( result.x > 0 ) {
		result.x = 1;
	}
	if ( result.y > 0 ) {
		result.y = 1;
	}
	if ( result.x < 0 ) {
		result.x = -1;
	}
	if ( result.y < 0 ) {
		result.y = -1;
	}
	return result;
}