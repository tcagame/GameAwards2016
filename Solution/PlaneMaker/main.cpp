#include "Framework.h"
#include "Model.h"
#include "DxLib.h"

void makePlain( ) {
	const double T = 0.0625;

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
		if ( i & 0x01 ) {
			model->set( idx++, Model::VERTEX( Vector( -1, -1, 0 ), 0, 0 ) );
			model->set( idx++, Model::VERTEX( Vector(  0, -1, 0 ), T, 0 ) );
			model->set( idx++, Model::VERTEX( Vector(  0,  0, 0 ), T, T ) );
			model->set( idx++, Model::VERTEX( Vector( -1, -1, 0 ), 0, 0 ) );
			model->set( idx++, Model::VERTEX( Vector(  0,  0, 0 ), T, T ) );
			model->set( idx++, Model::VERTEX( Vector( -1,  0, 0 ), 0, T ) );
		}
		if ( i & 0x02 ) {
			model->set( idx++, Model::VERTEX( Vector(  0, -1, 0 ), T    , 0 ) );
			model->set( idx++, Model::VERTEX( Vector(  1, -1, 0 ), 2 * T, 0 ) );
			model->set( idx++, Model::VERTEX( Vector(  1,  0, 0 ), 2 * T, T ) );
			model->set( idx++, Model::VERTEX( Vector(  0, -1, 0 ), T    , 0 ) );
			model->set( idx++, Model::VERTEX( Vector(  1,  0, 0 ), 2 * T, T ) );
			model->set( idx++, Model::VERTEX( Vector(  0,  0, 0 ), T    , T ) );
		}
		if ( i & 0x04 ) {
			model->set( idx++, Model::VERTEX( Vector( -1,  0, 0 ), 0, T     ) );
			model->set( idx++, Model::VERTEX( Vector(  0,  0, 0 ), T, T     ) );
			model->set( idx++, Model::VERTEX( Vector(  0,  1, 0 ), T, 2 * T ) );
			model->set( idx++, Model::VERTEX( Vector( -1,  0, 0 ), 0, T     ) );
			model->set( idx++, Model::VERTEX( Vector(  0,  1, 0 ), T, 2 * T ) );
			model->set( idx++, Model::VERTEX( Vector( -1,  1, 0 ), 0, 2 * T ) );
		}
		if ( i & 0x08 ) {
			model->set( idx++, Model::VERTEX( Vector(  0,  0, 0 ), T    , T     ) );
			model->set( idx++, Model::VERTEX( Vector(  1,  0, 0 ), 2 * T, T     ) );
			model->set( idx++, Model::VERTEX( Vector(  1,  1, 0 ), 2 * T, 2 * T ) );
			model->set( idx++, Model::VERTEX( Vector(  0,  0, 0 ), T    , T     ) );
			model->set( idx++, Model::VERTEX( Vector(  1,  1, 0 ), 2 * T, 2 * T ) );
			model->set( idx++, Model::VERTEX( Vector(  0,  1, 0 ), T    , 2 * T ) );
		}
		char buf[ 1024 ];
		sprintf_s( buf, 1024, "p_%02d.mdl", i );
		model->save( buf );
	}
}

void makeDesert( ) {

}

void main( ) {
	makeDesert( );
	makePlain( );

	FrameworkPtr fw = Framework::getInstance( );
	fw->terminate( );
}