#include "App.h"
#include "Framework.h"
#include "Map.h"
#include "Miners.h"
#include "Pioneers.h"
#include "MinersFactorys.h"
#include "GoldMines.h"
#include "Forests.h"

AppPtr App::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< App >( fw->getTask( getTag( ) ) );
}

App::App( ) {
}

App::~App( ) {
}

void App::initialize( ) {
	_gold = 0;

	_map = MapPtr( new Map );
	_miners = MinersPtr( new Miners );
	_pioneers = PioneersPtr( new Pioneers );
	_gold_mines = GoldMinesPtr( new GoldMines( _map ) );
	_miners_factorys = MinersFactorysPtr( new MinersFactorys( _map ) );
	_forests = ForestsPtr( new Forests( _map ) );

	_forests->install( Coord( 4, 9 ) );
}

void App::update( ) {
	_miners_factorys->update( );
	_miners->update( );
}

MapConstPtr App::getMap( ) const{
	return _map;
}

MapPtr App::getMap( ) {
	return _map;
}

MinersPtr App::getMiners( ) {
	return _miners;
}

PioneersPtr App::getPioneers( ) {
	return _pioneers;
}

GoldMinesPtr App::getGoldMines( ) {
	return _gold_mines;
}

MinersFactorysPtr App::getMinersFactorys( ) {
	return _miners_factorys;
}

void App::addGold( int gold ) {
	_gold += gold;
}

ForestsPtr App::getForests( ) {
	return _forests;
}