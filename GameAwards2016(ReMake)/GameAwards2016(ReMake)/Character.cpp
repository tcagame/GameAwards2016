#include "Character.h"
#include "App.h"
#include "mathmatics.h"
#include "Map.h"
#include "Material.h"
#include "GoldMines.h"
#include "GoldMine.h"
#include "Forests.h"
#include "Forest.h"
#include <array>
#include <queue>

Character::Character( const std::vector<Coord>& root, const Coord& target_pos ) :
_pos( root[ 0 ] ) {
	Ratio temp;
	const int RATIO_MAX = temp.RATIO_ACCURACY;
	_speed = RATIO_MAX / 10;
	_root_key = 0;
	_root = root;
	_target_pos = target_pos;
	setCoord( root[ 0 ] );
}

Character::~Character( ) {
}

void Character::update( ) {
	move( );
	action( );
}

void Character::getRootPoint( ) {
	_root_point = _pos.getCoordWithRatio( );
	if ( !existMaterial( _target_pos ) && _root_key == 0 ) {
		return;
	}
	if ( ( int )_root.size( ) == 1 ) {
		return;
	}

	if ( _root_key < ( int )_root.size( ) - 1 ) {
		if ( _pos.getCoordWithRatio( ) == _root_point ) {
			_root_key++;
			_root_key %= ( int )_root.size( );
		}
	}
	_root_point = RatioCoord( Coord( _root[ _root_key ].x, _root[ _root_key ].y ) ).getCoordWithRatio( );
}

void Character::move( ) {
	getRootPoint( );
	Vector dir = _root_point - Vector( getCoord( ).x, getCoord( ).y );
	Vector vec = dir.normalize( ) * _speed;
	_pos.increase( Coord( ( int )vec.x, ( int )vec.y ) );

	setCoord( _pos.getPos( ) );
}

bool Character::existMaterial( Coord pos ) {
	AppPtr app = App::getTask( );
	MapPtr map = app->getMap( );
	Map::Chip chip = map->getChip( pos );
	if ( chip.type == CHIP_TYPE_GOLD_MINE ) {
		GoldMinesPtr goldmines = app->getGoldMines( );
		GoldMinePtr goldmine = goldmines->get( chip.value );
		return goldmine->isExist( );
	}
	
	if ( chip.type == CHIP_TYPE_FOREST ) {
		ForestsPtr forests = app->getForests( );
		ForestPtr forest = forests->get( chip.value );
		return forest->isExist( );
	}
	return false;
}

RatioCoord Character::getRatioCoord( ) {
	return _pos;
}