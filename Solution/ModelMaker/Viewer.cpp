#include "Viewer.h"
#include "Framework.h"
#include "Drawer.h"
#include "MapChip.h"
#include "GroundChip.h"
#include "MapMaker.h"
#include "Model.h"
#include "FileManager.h"
#include <assert.h>

const int CHIP_SIZE = 128;
const int DIFF_X = CHIP_SIZE / 2;
const int DIFF_Y = CHIP_SIZE / 2;

enum RES {
	RES_TEXTURE,
	MAX_RES,
};

ViewerPtr Viewer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Viewer >( fw->getTask( getTag( ) ) );
}

Viewer::Viewer( MapMakerPtr map_maker, FileManagerPtr file_manager, ModelPtr model ) {
	_map_maker = map_maker;
	_file_manager = file_manager;
	_model = model;
}

Viewer::~Viewer( ) {
}

void Viewer::initialize( ) {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->load( RES_TEXTURE, "GroudTexture.png" );
}

void Viewer::update( ) {
	drawMap( );
}

void Viewer::drawMap( ) const {
	/*for ( int i = 0; i < _map_maker->getWidth( ); i++ ) {
		for ( int j = 0; j < _map_maker->getHeight( ); j++ ) {
			drawPlain( i, j );
			drawDesert( i, j );
			drawMountain( i, j );
			drawRiver( i, j );
		}
	}*/
	_model->draw( );
}


void Viewer::drawPlain( int mx, int my ) const {
	
	int idx = _map_maker->getMapType( mx, my, GROUND_CHIP_TYPE_PLAIN );
	if ( idx == MAP_TYPE_FFFF ) {
		return;
	}
	DrawerPtr drawer = Drawer::getTask( );
	int x = mx * CHIP_SIZE;
	int y = my * CHIP_SIZE;
	unsigned char key = 0x08;
	for ( int i = 0 ;i < 4; i++ ) {
		if ( ( idx | key ) > 0 ) {
			int tx = i % 2 * ( CHIP_SIZE / 2 );
			int ty = i / 2 * ( CHIP_SIZE / 2 );
			int sx = x + tx;
			int sy = y + ty;
			drawer->set( Drawer::Sprite( Drawer::Transform( sx + DIFF_X, sy + DIFF_Y, tx, ty, CHIP_SIZE / 2,CHIP_SIZE / 2 ),RES_TEXTURE ) );
		}
		key = key >> 1;
	}
}

void Viewer::drawDesert( int mx, int my ) const {
	int idx = _map_maker->getMapType( mx, my, GROUND_CHIP_TYPE_DESERT );
	if ( idx == MAP_TYPE_FFFF ) {
		return;
	}
	DrawerPtr drawer = Drawer::getTask( );
	int sx = mx * CHIP_SIZE;
	int sy = my * CHIP_SIZE;
	int tx = idx % 8 * CHIP_SIZE;
	int ty = ( GROUND_CHIP_TYPE_DESERT * 2 + idx / 8 ) * CHIP_SIZE;
	drawer->set( Drawer::Sprite( Drawer::Transform( sx + DIFF_X, sy + DIFF_Y, tx, ty, CHIP_SIZE,CHIP_SIZE ),RES_TEXTURE ) );
}

void Viewer::drawMountain( int mx, int my ) const {
	int idx = _map_maker->getMapType( mx, my, GROUND_CHIP_TYPE_MOUNTAIN );
	if ( idx == MAP_TYPE_FFFF ) {
		return;
	}
	DrawerPtr drawer = Drawer::getTask( );
	int sx = mx * CHIP_SIZE;
	int sy = my * CHIP_SIZE;
	int tx = idx % 8 * CHIP_SIZE;
	int ty = ( GROUND_CHIP_TYPE_MOUNTAIN * 2 + idx / 8 ) * CHIP_SIZE;
	drawer->set( Drawer::Sprite( Drawer::Transform( sx + DIFF_X, sy + DIFF_Y, tx, ty, CHIP_SIZE,CHIP_SIZE ),RES_TEXTURE ) );
}

void Viewer::drawRiver( int mx, int my ) const {
	int idx = _map_maker->getMapType( mx, my, GROUND_CHIP_TYPE_RIVER );
	if ( idx == MAP_TYPE_FFFF ) {
		return;
	}
	DrawerPtr drawer = Drawer::getTask( );
	int sx = mx * CHIP_SIZE;
	int sy = my * CHIP_SIZE;
	int tx = idx % 8 * CHIP_SIZE;
	int ty = ( GROUND_CHIP_TYPE_RIVER * 2 + idx / 8 ) * CHIP_SIZE;
	drawer->set( Drawer::Sprite( Drawer::Transform( sx + DIFF_X, sy + DIFF_Y, tx, ty, CHIP_SIZE,CHIP_SIZE ),RES_TEXTURE ) );
}