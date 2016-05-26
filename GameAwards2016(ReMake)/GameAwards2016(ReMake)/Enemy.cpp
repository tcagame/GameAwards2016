#include "Enemy.h"
#include "Map.h"
#include "mathmatics.h"
#include "Character.h"

const int WIDTH = 2;
const int HEIGHT = 2;
const int HP = 1000000;

Enemy::Enemy( const Coord& pos ) :
_width( WIDTH ),
_height( HEIGHT ) {
	_hp = HP;
	setCoord( pos );
}

Enemy::~Enemy( ) {
}

void Enemy::update( ) {
	searchTarget( );
	move( );
}

void Enemy::move( ) {
	Vector dir = Vector( );
	if ( !_target.expired( ) ) {
		CharacterPtr character = _target.lock( );
		Coord character_coord = character->getCoord( );
		Vector target_pos = Vector( character_coord.x, character_coord.y );
		dir = target_pos - Vector( getCoord( ).x, getCoord( ).y );
	}
	Coord pos = getCoord( );
	pos.x += ( int )( dir.x * _speed );
	pos.y += ( int )( dir.y * _speed );
	setCoord( pos );
}

bool Enemy::isExist( ) {
	if ( _hp <= 0 ) {
		return false;
	}
	return true;
}

void Enemy::searchTarget( ) {

}