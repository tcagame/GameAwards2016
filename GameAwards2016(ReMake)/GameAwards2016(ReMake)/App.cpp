#include "App.h"
#include "Framework.h"
#include "Map.h"
#include "Miners.h"
#include "Pioneers.h"
#include "MinersFactorys.h"
#include "PioneersFactorys.h"
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
	_forests = ForestsPtr( new Forests( _map ) );
	_miners_factorys = MinersFactorysPtr( new MinersFactorys( _map ) );
	_pioneers_factorys = PioneersFactorysPtr( new PioneersFactorys( _map ) );

	_forests->install( Coord( 5, 10 ) );
	_pioneers_factorys->install( Coord( 5, 5 ) );
	_gold_mines->install( Coord( 10, 5 ) );
	_gold_mines->install( Coord( 15, 5 ) );
	_miners_factorys->install( Coord( 10, 10 ) );
	_miners_factorys->install( Coord( 18, 10 ) );
}

void App::update( ) {
	_miners_factorys->update( );
	_pioneers_factorys->update( );
	_miners->update( );
	_pioneers->update( );
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

PioneersFactorysPtr App::getPioneersFactorys( ) {
	return _pioneers_factorys;
}

void App::addGold( int gold ) {
	_gold += gold;
}

ForestsPtr App::getForests( ) {
	return _forests;
}