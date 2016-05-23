#pragma once
#include "Task.h"
#include <string>

PTR( App );
PTR( Map );
PTR( Miners );
PTR( Pioneers );
PTR( MinersFactorys );
PTR( GoldMines );
PTR( Forests );

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
	MinersFactorysPtr getMinersFactorys( );
	GoldMinesPtr getGoldMines( );
	ForestsPtr getForests( );
	void addGold( int gold );
public:
	int _gold;
	MapPtr _map;
	MinersPtr _miners;
	PioneersPtr _pioneers;
	MinersFactorysPtr _miners_factorys;
	GoldMinesPtr _gold_mines;
	ForestsPtr _forests;
};

