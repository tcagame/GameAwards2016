#pragma once
#include "Task.h"
#include <string>

PTR( App );
PTR( Map );
PTR( UnitMap )
PTR( Miners );
PTR( Pioneers );
PTR( Guardians );
PTR( MinersFactorys );
PTR( PioneersFactorys );
PTR( GuardiansFactories );
PTR( GoldMines );
PTR( Forests );
PTR( Enemies );

class App : public Task {
public:
	static AppPtr getTask( );
	static std::string getTag( ) { return "APP"; }
public:
	App( );
	virtual ~App( );
public:
	void initialize( );
	void update( );
	MapConstPtr getMap( ) const;
	MapPtr getMap( );
	UnitMapPtr getUnitMap( );
	MinersPtr getMiners( );
	PioneersPtr getPioneers( );
	EnemiesPtr getEnemies( );
	MinersFactorysPtr getMinersFactorys( );
	PioneersFactorysPtr getPioneersFactorys( );
	GuardiansFactoriesPtr getGuardiansFactories( );
	GoldMinesPtr getGoldMines( );
	GuardiansPtr getGuardians( );
	ForestsPtr getForests( );
	void addGold( int gold );
public:
	int _gold;
	MapPtr _map;
	UnitMapPtr _unit_map;
	MinersPtr _miners;
	PioneersPtr _pioneers;
	EnemiesPtr _enemies;
	MinersFactorysPtr _miners_factorys;
	PioneersFactorysPtr _pioneers_factorys;
	GuardiansFactoriesPtr _guardians_factories;
	GoldMinesPtr _gold_mines;
	GuardiansPtr _guardians;
	ForestsPtr _forests;
};

