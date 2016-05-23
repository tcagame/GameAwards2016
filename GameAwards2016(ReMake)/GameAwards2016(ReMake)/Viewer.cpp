#include "Viewer.h"
#include "Drawer.h"
#include "App.h"
#include "GoldMines.h"
#include "GoldMine.h"
#include "MinersFactorys.h"
#include "MinersFactory.h"
#include "Miners.h"
#include "Miner.h"
#include "Forests.h"
#include "Forest.h"
#include "Coord.h"
#include <vector>

static const int CHIP_SIZE = 32;

enum RES {
	RES_NONE,
	RES_GROUND,
	RES_GOLD_MINE,
	RES_MINERS_FACTORY,
	RES_MINER,
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
	drawer->load( RES_MINER, "resource/Graph/Miner.png" );
	drawer->load( RES_ROOT, "resource/Graph/root.png" );
	drawer->load( RES_FOREST, "resource/Graph/forest.png" );
}

void Viewer::update( ) {
	drawGround( );
	drawRoot( );
	drawGoldMine( );
	drawMinersFactorys( );
	drawMiner( );
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

void Viewer::drawRoot( ) {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
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

void Viewer::drawForest( ) {
	AppPtr app = App::getTask( );
	if ( !app ) {
		return;
	}
	ForestsPtr forests = app->getForests( );
	const int size = forests->getSize( );
	for ( int i = 0; i < size; i++ ) {
		ForestPtr forest = forests->get( i );
		int sx = forest->getCoord( ).x * CHIP_SIZE;
		int sy = forest->getCoord( ).y * CHIP_SIZE;
		DrawerPtr drawer = Drawer::getTask( );
		drawer->set( Drawer::Sprite( Drawer::Transform( sx, sy ), RES_FOREST ) );
	}
}