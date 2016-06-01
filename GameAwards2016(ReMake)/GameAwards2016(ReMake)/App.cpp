#include "App.h"
#include "Framework.h"
#include "Map.h"
#include "Miners.h"
#include "Pioneers.h"
#include "Enemies.h"
#include "MinersFactorys.h"
#include "PioneersFactorys.h"
#include "GuardiansFactories.h"
#include "GoldMines.h"
#include "Guardians.h"
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
	_enemies = EnemiesPtr( new Enemies );
	_gold_mines = GoldMinesPtr( new GoldMines( _map ) );
	_guardians = GuardiansPtr( new Guardians );
	_forests = ForestsPtr( new Forests( _map ) );
	_miners_factorys = MinersFactorysPtr( new MinersFactorys( _map ) );
	_pioneers_factorys = PioneersFactorysPtr( new PioneersFactorys( _map ) );
	_guardians_factories = GuardiansFactoriesPtr( new GuardiansFactories( _map ) );

	_gold_mines->install( Coord( 5, 10 ) );
	_enemies->create( Coord( 1, 0 ) );
	_guardians_factories->install( Coord( 5, 15 ) );
}

void App::update( ) {
	_miners_factorys->update( );
	_pioneers_factorys->update( );
	_guardians_factories->update( );
	_miners->update( );
	_guardians->update( );
	_pioneers->update( );
	_enemies->update( );
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

EnemiesPtr App::getEnemies( ) {
	return _enemies;
}	

GoldMinesPtr App::getGoldMines( ) {
	return _gold_mines;
}

GuardiansPtr App::getGuardians( ) {
	return _guardians;
}

MinersFactorysPtr App::getMinersFactorys( ) {
	return _miners_factorys;
}

PioneersFactorysPtr App::getPioneersFactorys( ) {
	return _pioneers_factorys;
}

GuardiansFactoriesPtr App::getGuardiansFactories( ) {
	return _guardians_factories;
}

void App::addGold( int gold ) {
	_gold += gold;
}

ForestsPtr App::getForests( ) {
	return _forests;
}