#include "Viewer.h"
#include "Drawer.h"
#include "App.h"
#include "GoldMines.h"
#include "GoldMine.h"
#include "Forests.h"
#include "Forest.h"
#include "MinersFactorys.h"
#include "MinersFactory.h"
#include "PioneersFactorys.h"
#include "PioneersFactory.h"
#include "GuardiansFactories.h"
#include "GuardiansFactory.h"
#include "Miners.h"
#include "Miner.h"
#include "Pioneers.h"
#include "Pioneer.h"
#include "Enemies.h"
#include "Enemy.h"
#include "Guardians.h"
#include "Guardian.h"
#include "Coord.h"
#include <vector>

static const int CHIP_SIZE = 32;

enum RES {
	RES_NONE,
	RES_GROUND,
	RES_GOLD_MINE,
	RES_MINERS_FACTORY,
	RES_PIONEERS_FACTORY,
	RES_GUARDIAN_FACTORY,
	RES_MINER,
	RES_PIONEER,
	RES_GUARDIAN,
	RES_ENEMY,
	RES_ROOT,
	RES_FOREST,
	MAX_RES,
};

Viewer::Viewer( ) {
}

Viewer::~Viewer( ) {
}

void Viewer::initialize( ) {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->load( RES_GROUND, "resource/Graph/ground.png" );
	drawer->load( RES_GOLD_MINE, "resource/Graph/GoldMine.png" );
	drawer->load( RES_MINERS_FACTORY, "resource/Graph/MinersFactory.png" );
	drawer->load( RES_PIONEERS_FACTORY, "resource/Graph/PioneersFactory.png" );
	drawer->load( RES_GUARDIAN_FACTORY, "resource/Graph/GuardiansFactory.png" );
	drawer->load( RES_MINER, "resource/Graph/Miner.png" );
	drawer->load( RES_PIONEER, "resource/Graph/Pioneer.png" );
	drawer->load( RES_GUARDIAN, "resource/Graph/Guardian.png" );
	drawer->load( RES_ROOT, "resource/Graph/root.png" );
	drawer->load( RES_FOREST, "resource/Graph/forest.png" );
	drawer->load( RES_ENEMY, "resource/Graph/Enemy.png" );
}

void Viewer::update( ) {
	drawGround( );
	drawRoot( );
	drawGoldMine( );
	drawMinersFactorys( );
	drawPioneersFactorys( );
	drawGuardiansFactories( );
	drawMiner( );
	drawPioneer( );
	drawEnemy( );
	drawGuardian( );
	drawForest( );
}

void Viewer::drawGround( ) {
	DrawerPtr drawer = Drawer::getTask( );
	for ( int j = 0; j < COORD_HEIGHT; j++ ) {
		for ( int i = j % 2; i < COORD_WIDTH; i += 2 ) {
			Drawer::Sprite sprite( Drawer::Transform( i * CHIP_SIZE - CHIP_SIZE, j * CHIP_SIZE ), RES_GROUND );
			drawer->set( sprite );
		}
	}
}

void Viewer::drawGoldMine( ) {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	GoldMinesPtr gold_mines = app->getGoldMines( );
	const int size = gold_mines->getSize( );
	for ( int i = 0; i < size; i++ ) {
		GoldMinePtr gold_mine = gold_mines->get( i );
		int sx = gold_mine->getCoord( ).x * CHIP_SIZE;
		int sy = gold_mine->getCoord( ).y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_GOLD_MINE ) );
	}
}

void Viewer::drawMinersFactorys( ) {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	MinersFactorysPtr miners_factorys = app->getMinersFactorys( );
	const int size = miners_factorys->getSize( );
	for ( int i = 0; i < size; i++ ) {
		MinersFactoryPtr miners_factory = miners_factorys->get( i );
		int sx = miners_factory->getCoord( ).x * CHIP_SIZE;
		int sy = miners_factory->getCoord( ).y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_MINERS_FACTORY ) );
	}
}

void Viewer::drawPioneersFactorys( ) {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	PioneersFactorysPtr pioneers_factorys = app->getPioneersFactorys( );
	const int size = pioneers_factorys->getSize( );
	for ( int i = 0; i < size; i++ ) {
		PioneersFactoryPtr pioneers_factory = pioneers_factorys->get( i );
		int sx = pioneers_factory->getCoord( ).x * CHIP_SIZE;
		int sy = pioneers_factory->getCoord( ).y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_PIONEERS_FACTORY ) );
	}
}

void Viewer::drawGuardiansFactories( ) {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	GuardiansFactoriesPtr guardians_factories = app->getGuardiansFactories( );
	const int size = guardians_factories->getSize( );
	for ( int i = 0; i < size; i++ ) {
		GuardiansFactoryPtr guardians_factory = guardians_factories->get( i );
		int sx = guardians_factory->getCoord( ).x * CHIP_SIZE;
		int sy = guardians_factory->getCoord( ).y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_GUARDIAN_FACTORY ) );
	}
}

void Viewer::drawMiner( ) {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	MinersPtr miners = app->getMiners( );
	const int size = miners->getSize( );
	for ( int i = 0; i < size; i++ ) {
		MinerPtr miner = miners->get( i );
		int sx = miner->getCoord( ).x * CHIP_SIZE;
		int sy = miner->getCoord( ).y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_MINER ) );
	}
}

void Viewer::drawPioneer( ) {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	PioneersPtr pioneers = app->getPioneers( );
	const int size = pioneers->getSize( );
	for ( int i = 0; i < size; i++ ) {
		PioneerPtr pioneer = pioneers->get( i );
		int sx = pioneer->getCoord( ).x * CHIP_SIZE;
		int sy = pioneer->getCoord( ).y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_PIONEER ) );
	}
}

void Viewer::drawEnemy( ) {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	EnemiesPtr enemies = app->getEnemies( );
	const int size = enemies->getSize( );
	for ( int i = 0; i < size; i++ ) {
		EnemyPtr enemy = enemies->get( i );
		int sx = enemy->getCoord( ).x * CHIP_SIZE;
		int sy = enemy->getCoord( ).y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_ENEMY ) );
	}
}

void Viewer::drawGuardian( ) {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	GuardiansPtr Guardians = app->getGuardians( );
	const int size = Guardians->getSize( );
	for ( int i = 0; i < size; i++ ) {
		GuardianPtr Guardian = Guardians->get( i );
		int sx = Guardian->getCoord( ).x * CHIP_SIZE;
		int sy = Guardian->getCoord( ).y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_GUARDIAN ) );
	}
}

void Viewer::drawRoot( ) {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	
	{//マイナールート
		MinersFactorysPtr miners_factorys = app->getMinersFactorys( );
		const int size = miners_factorys->getSize( );
		for ( int i = 0; i < size; i++ ) {
			MinersFactoryPtr miners_factory = miners_factorys->get( i );
			std::vector<Coord> root = miners_factory->getRoot( ); 
			for ( int j = 0; j < ( int )root.size( ); j++ ) {
				int sx = root[ j ].x * CHIP_SIZE;
				int sy = root[ j ].y * CHIP_SIZE;
				DrawerPtr drawer = Drawer::getTask( );
				drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_ROOT, Drawer::BLEND_ALPHA, 0.5 ) );
			}
		}
	}

	{//パイオニアルート
		PioneersFactorysPtr pioneers_factorys = app->getPioneersFactorys( );
		const int size = pioneers_factorys->getSize( );
		for ( int i = 0; i < size; i++ ) {
			PioneersFactoryPtr pioneers_factory = pioneers_factorys->get( i );
			std::vector<Coord> root = pioneers_factory->getRoot( ); 
			for ( int j = 0; j < ( int )root.size( ); j++ ) {
				int sx = root[ j ].x * CHIP_SIZE;
				int sy = root[ j ].y * CHIP_SIZE;
				DrawerPtr drawer = Drawer::getTask( );
				drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_ROOT, Drawer::BLEND_ALPHA, 0.5 ) );
			}
	
		}
	}
}

void Viewer::drawForest( ) {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	ForestsPtr forests = app->getForests( );
	const int size = forests->getSize( );
	for ( int i = 0; i < size; i++ ) {
		ForestPtr forest = forests->get( i );
		if ( forest->isExist( ) ) {
			int sx = forest->getCoord( ).x * CHIP_SIZE;
			int sy = forest->getCoord( ).y * CHIP_SIZE;
			DrawerPtr drawer = Drawer::getTask( );
			drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_FOREST ) );
		}
	}
}