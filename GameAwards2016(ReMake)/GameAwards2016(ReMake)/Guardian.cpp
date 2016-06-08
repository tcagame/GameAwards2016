#include "Guardian.h"
#include "App.h"
#include "Map.h"
#include "UnitMap.h"
#include "GuardiansFactories.h"
#include "GuardiansFactory.h"
#include "Enemies.h"
#include "Enemy.h"
#include "CharacterType.cpp"

static const int POWER = 1000;
static const Coord FACTORY_DIFF = Coord( 1, 3 );
static const int SEARCH_RANGE = 1;

Guardian::Guardian( const std::vector<Coord>& root, const Coord& factory_pos ) :
_pos( root[ 0 ] ),
_factory_pos( factory_pos ) {
	int RATIO_MAX = _pos.getRatio( ).x.RATIO_ACCURACY;
	_speed = RATIO_MAX / 10;
	_root = root;
	_time = 0;
	setCoord( root[ 0 ] );
	_is_attack = false;
	_target = _pos.getCoordWithRatio( );
}

Guardian::~Guardian( ) {
}

void Guardian::action( ) {
	AppPtr app = App::getTask( );
	UnitMapPtr unit_map = app->getUnitMap( );
	UnitMap::Chip chip = unit_map->getChip( _pos.getCoord( ) );

	EnemiesPtr enemies = app->getEnemies( );
	for ( int i = 0; i < ( int )enemies->getSize( ); i++ ) {
		if ( chip.type == CHARACTER_TYPE_ENEMY && chip.value == i ) {
			EnemyPtr enemy = enemies->get( i );
			 enemy->damage( POWER );
		}
	}
}

void Guardian::update( ) {
	move( );
	if ( !existEnemy( ) ) {
		searchEnemy( );
	}
	action( );
}

void Guardian::getRootPoint( ) {
	if ( existEnemy( ) ) {
		EnemyPtr enemy = _enemy.lock( );
		Coord ep = enemy->getCoord( );
		_target = RatioCoord( ep ).getCoordWithRatio( );
		return;
	}

	if ( ( int )_root.size( ) == 1 ) {
		_target = _pos.getCoordWithRatio( );
		return;
	}
	Coord target = Coord( ( int )_target.x, ( int )_target.y );
	if ( target.getIdx( ) == _pos.getCoord( ).getIdx( ) ) {
		int key;
		for ( int i = 0; i < ( int )_root.size( ); i++ ) {
			if ( _root[ i ].getIdx( ) == _pos.getCoord( ).getIdx( ) ) {
				key = i;
				key++;
				key %= ( int )_root.size( );
				break;
			}
		}
		_target = RatioCoord( _root[ key ] ).getCoordWithRatio( );
	}
}

void Guardian::move( ) {
	AppPtr app = App::getTask( );
	MapPtr map = app->getMap( );
	
	getRootPoint( );
	Vector dir = _target - _pos.getCoordWithRatio( );
	dir = dir.normalize( );
	RatioCoord after_pos( _pos.getCoord( ) );
	after_pos.increase( Coord( ( int )( dir.x * _speed ), ( int )( dir.y * _speed ) ) );
	Map::Chip chip = map->getChip( after_pos.getCoord( ) );
	if ( chip.type != CHIP_TYPE_NONE && chip.type != CHIP_TYPE_GUARDIAN ) {
		Vector factory_pos = _factory_pos.getCoordWithRatio( );
		Vector dir_for_factory = factory_pos - _pos.getCoordWithRatio( );
		dir =dir_for_factory.normalize( );
	}
	_pos.increase( Coord( ( int )( dir.x * _speed ), ( int )( dir.y * _speed ) ) );
	setCoord( _pos.getCoord( ) );
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

RatioCoord Guardian::getRatioCoord( ) {
	return _pos;
}