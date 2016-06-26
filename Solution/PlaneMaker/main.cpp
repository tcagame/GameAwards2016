#include "Framework.h"
#include "Model.h"
#include "DxLib.h"

const double CHIP_SIZE = 0.5;
const double TEXTURE_SIZE = 0.125;
const double T = TEXTURE_SIZE / 2;

enum TEXTURE_TYPE {
	TEXTURE_TYPE_PLAIN,
	TEXTURE_TYPE_DESERT,
	TEXTURE_TYPE_MOUNTAIN,
	TEXTURE_TYPE_RIVER,
	TEXTURE_TYPE_MAX
};

const std::string MODEL_NAME[ TEXTURE_TYPE_MAX ] = {
	"plain",
	"desert",
	"mountain",
	"river"
};

void makePlane ( int type ) {
	for ( int i = 1; i < 16; i++ ) {
		ModelPtr model = ModelPtr( new Model( ) );
		int polygon_num = 
			( ( i & 0x01 ) != 0 ) +
			( ( i & 0x02 ) != 0 ) +
			( ( i & 0x04 ) != 0 ) +
			( ( i & 0x08 ) != 0 );
		polygon_num *= 2;
		model->alloc( polygon_num );

		int idx = 0;

		double tex_pos_x;
		double tex_pos_y;
		if ( type == TEXTURE_TYPE_PLAIN ) {
			tex_pos_x = 0;
			tex_pos_y = 0;
		} else { 
			tex_pos_x = i % 8;
			tex_pos_x *= TEXTURE_SIZE;
			tex_pos_y = type * 2 + i / 8;
			tex_pos_y *= TEXTURE_SIZE;
		}

		if ( i & 0x01 ) {
			model->set( idx++, Model::VERTEX( Vector( -CHIP_SIZE, -CHIP_SIZE, 0 ), tex_pos_x, tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector(  0, -CHIP_SIZE, 0 ), T + tex_pos_x, tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector(  0,  0, 0 ), T + tex_pos_x, T + tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector( -CHIP_SIZE, -CHIP_SIZE, 0 ), tex_pos_x, tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector(  0,  0, 0 ), T + tex_pos_x, T + tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector( -CHIP_SIZE,  0, 0 ), tex_pos_x, T + tex_pos_y ) );
		}
		if ( i & 0x02 ) {
			model->set( idx++, Model::VERTEX( Vector(  0, -CHIP_SIZE, 0 ), T + tex_pos_x    , tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE, -CHIP_SIZE, 0 ), 2 * T + tex_pos_x, tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE,  0, 0 ), 2 * T + tex_pos_x, T + tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector(  0, -CHIP_SIZE, 0 ), T + tex_pos_x    , tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE,  0, 0 ), 2 * T + tex_pos_x, T + tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector(  0,  0, 0 ), T + tex_pos_x, T + tex_pos_y ) );
		}
		if ( i & 0x04 ) {
			model->set( idx++, Model::VERTEX( Vector( -CHIP_SIZE,  0, 0 ), tex_pos_x, T + tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector(  0,  0, 0 ), T + tex_pos_x, T + tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector(  0, CHIP_SIZE, 0 ), T + tex_pos_x, 2 * T + tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector( -CHIP_SIZE,  0, 0 ), tex_pos_x, T + tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector(  0, CHIP_SIZE, 0 ), T + tex_pos_x, 2 * T + tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector( -CHIP_SIZE, CHIP_SIZE, 0 ), tex_pos_x, 2 * T + tex_pos_y ) );
		}
		if ( i & 0x08 ) {
			model->set( idx++, Model::VERTEX( Vector(  0,  0, 0 ), T + tex_pos_x, T + tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE,  0, 0 ), 2 * T + tex_pos_x, T + tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE, CHIP_SIZE, 0 ), 2 * T + tex_pos_x, 2 * T + tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector(  0,  0, 0 ), T + tex_pos_x, T + tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector( CHIP_SIZE, CHIP_SIZE, 0 ), 2 * T + tex_pos_x, 2 * T + tex_pos_y ) );
			model->set( idx++, Model::VERTEX( Vector(  0, CHIP_SIZE, 0 ), T + tex_pos_x, 2 * T + tex_pos_y ) );
		}
		char buf[ 1024 ];
		sprintf_s( buf, 1024, "_%02d.mdl", i );
		std::string filename = MODEL_NAME[ type ] + buf;
		model->save( filename );
	}
}

void main( ) {
	for ( int i = 0; i < TEXTURE_TYPE_MAX; i++ ) {
		makePlane( i );
	}
	FrameworkPtr fw = Framework::getInstance( );
	fw->terminate( );
}