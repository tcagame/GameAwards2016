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
_pos( root[ 0 ] ),
_pop_point( root[ 0 ] ){
	Ratio temp;
	const int RATIO_MAX = temp.RATIO_ACCURACY;
	_speed = RATIO_MAX / 10;
	_root = root;
	_target_pos = target_pos;
	setCoord( root[ 0 ] );
	_root_point = Vector( root[ 0 ].x, root[ 0 ].y );
}

Character::~Character( ) {
}

void Character::update( ) {
	move( );
	action( );
}

void Character::getRootPoint( ) {
	double length = ( _pos.getCoordWithRatio( ) - _pop_point.getCoordWithRatio( )).getLength( );
	if ( !existMaterial( _target_pos ) && length < 0.4 ) {
		_root_point =_pos.getCoordWithRatio( );
		return;
	}
	if ( ( int )_root.size( ) == 1 ) {
		_root_point = _pos.getCoordWithRatio( );
		return;
	}

	//‚±‚±‚ð•Ï‚¦‚é
	Coord root_coord = Coord( ( int )_root_point.x, ( int )_root_point.y );
	if ( _pos.getCoord( ).getIdx( ) == root_coord.getIdx( ) ) {
		int root_key;
		for ( int i = 0; i < ( int )_root.size( ); i++ ) {
			if ( _pos.getCoord( ).getIdx( ) == _root[ i ].getIdx( ) ) {
				root_key = i;
				break;
			}
		}
		/*˜p‹È—pƒvƒƒOƒ‰ƒ€
		Vector point[ 3 ];
		for ( int i = 0; i < 3; i++ ) {
			int key = i + root_key;
			key %= ( int )_root.size( );
			point[ i ] = Vector( _root[ key ].x, _root[ key ].y );
		}
		*/
		int key = root_key + 1;
		key %= ( int )_root.size( );
		RatioCoord target( _root[ key ] );
		_root_point = target.getCoordWithRatio( );
	}
}

void Character::move( ) {
	getRootPoint( );
	Vector dir = _root_point - _pos.getCoordWithRatio( );
	Vector vec = dir.normalize( ) * _speed;
	_pos.increase( Coord( ( int )vec.x, ( int )vec.y ) );

	setCoord( _pos.getCoord( ) );
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