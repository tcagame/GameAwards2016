#include "Guardian.h"
#include "App.h"
#include "Enemies.h"
#include "Enemy.h"

static const int POWER = 1000;
static const Coord FACTORY_DIFF = Coord( 1, 3 );
static const int SEARCH_RANGE = 1;

Guardian::Guardian( const std::vector<Coord>& root ) {
	_speed = 1;
	_target_key = 0;
	_root = root;
	_time = 0;
	setCoord( root[ 0 ] );
	_is_attack = false;
}

Guardian::~Guardian( ) {
}

void Guardian::action( ) {
	
}

void Guardian::update( ) {
	move( );
	if ( !existEnemy( ) ) {
		searchEnemy( );
	}
	action( );
}

void Guardian::getRootPoint( ) {
	Coord pos = getCoord( );
	if ( existEnemy( ) ) {
		EnemyPtr enemy = _enemy.lock( );
		Coord ep = enemy->getCoord( );
		_target = Vector( ep.x, ep.y );
		return;
	}

	if ( ( int )_root.size( ) == 1 ) {
		_target = Vector( getCoord( ).x, getCoord( ).y );
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

void Guardian::move( ) {
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

Vector Guardian::dirNomarize( const Vector& dir ) {
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

bool Guardian::existEnemy( ) {
	return !_enemy.expired( );
}

void Guardian::searchEnemy( ) {
	AppPtr app = App::getTask( );
	EnemiesPtr enemies = app->getEnemies( );
	for ( int i = 0; i < enemies->getSize( ); i++ ) {
		EnemyPtr enemy = enemies->get( i );
		Coord diff;
		diff.x = enemy->getCoord( ).x - getCoord( ).x;
		diff.y = enemy->getCoord( ).y - getCoord( ).y;
		diff.x = abs( diff.x );
		diff.y = abs( diff.y );
		if ( diff.x <= SEARCH_RANGE && diff.y <= SEARCH_RANGE ) {
			_enemy = enemy;
		}
	}
}
