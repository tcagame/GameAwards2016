#pragma once
#include "Task.h"
#include <string>

PTR( App );
PTR( Map );
PTR( Miners );
PTR( Pioneers );
PTR( MinersFactorys );
PTR( PioneersFactorys );
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
	MinersPtr getMiners( );
	PioneersPtr getPioneers( );
	EnemiesPtr getEnemies( );
	MinersFactorysPtr getMinersFactorys( );
	PioneersFactorysPtr getPioneersFactorys( );
	GoldMinesPtr getGoldMines( );
	ForestsPtr getForests( );
	void addGold( int gold );
public:
	int _gold;
	MapPtr _map;
	MinersPtr _miners;
	PioneersPtr _pioneers;
	EnemiesPtr _enemies;
	MinersFactorysPtr _miners_factorys;
	PioneersFactorysPtr _pioneers_factorys;
	GoldMinesPtr _gold_mines;
	ForestsPtr _forests;
};

