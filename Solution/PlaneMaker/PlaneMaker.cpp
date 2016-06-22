#include "PlaneMaker.h"
#include "Model.h"
#include "mathmatics.h"
#include <string>

const int CHIP_SIZE = 10;
const int TEXTURE_SIZE = 1024;
const int TEXTURE_CHIP_SIZE = TEXTURE_SIZE / 8;
const char NUMBER[ 16 ][ 3 ] = {
	"00",
	"01",
	"02",
	"03",
	"04",
	"05",
	"06",
	"07",
	"08",
	"09",
	"10",
	"11",
	"12",
	"13",
	"14",
	"15"
};

PlaneMaker::PlaneMaker( ) {
	makeModel( );
	save( );
}

PlaneMaker::~PlaneMaker( ) {
}

void PlaneMaker::makeModel( ) {
	for ( int i = 0; i < MAP_CHIP_NUM; i++ ) {
		makePlaneModel( i );
		makeDesertModel( i );
	}
}

void PlaneMaker::makePlaneModel( int id ) {
	if ( id == 0 ) {
		_plane[ id ] = ModelPtr( new Model( ) );
		return;
	}
	unsigned char key = 0x01;
	for ( int i = 0 ;i < 4; i++ ) {
		if ( ( id & key ) > 0 ) {
			int sx = i % 2 * ( CHIP_SIZE / 2 );
			int sy = i / 2 * ( CHIP_SIZE / 2 );
			int u = i % 2 * ( TEXTURE_CHIP_SIZE / 2 );
			int v = i / 2 * ( TEXTURE_CHIP_SIZE / 2 );
			setQuadranglePolygon( sx, sy, u, v, _plane[ i ] );
		}
		key = key << 1;
	}
}

void PlaneMaker::makeDesertModel( int id ) {
	if ( id == 0 ) {
		_desert[ id ] = ModelPtr( new Model( ) );
		return;
	}
	int tx = id % 8 * TEXTURE_CHIP_SIZE;
	int ty = ( 2 + id / 8 ) * TEXTURE_CHIP_SIZE;
	unsigned char key = 0x01;
	for ( int i = 0 ;i < 4; i++ ) {
		if ( ( id & key ) > 0 ) {
			int sx = i % 2 * ( CHIP_SIZE / 2 );
			int sy = i / 2 * ( CHIP_SIZE / 2 );
			int u = tx + i % 2 * ( TEXTURE_CHIP_SIZE / 2 );
			int v = ty + i / 2 * ( TEXTURE_CHIP_SIZE / 2 );
			setQuadranglePolygon( sx, sy, u, v, _desert[ i ] );
		}
		key = key << 1;
	}
}

void PlaneMaker::setQuadranglePolygon( int sx, int sy, int u, int v, ModelPtr model ) {
	Model::VERTEX vertex[ 4 ];
	Vector quad_point[ 4 ] = {
		Vector( 0, 0, 0 ),
		Vector( 1, 0, 0 ),
		Vector( 0, -1, 0 ),
		Vector( 1, -1, 0 ),
	};

	for ( int i = 0; i < 4; i++ ) {
		vertex[ i ].pos = Vector( ( double )sx, ( double ) sy, 0.0 ) + quad_point[ i ] * ( CHIP_SIZE / 2 );
		vertex[ i ].u = ( double )( u + i % 2 * ( TEXTURE_CHIP_SIZE / 2 ) ) / TEXTURE_SIZE;
		vertex[ i ].v = ( double )( v + i / 2 * ( TEXTURE_CHIP_SIZE / 2 ) ) / TEXTURE_SIZE;
	}

	Model::VERTEX quad_vertex[ 2 ][ 3 ] = {
		{ vertex[ 0 ], vertex[ 1 ], vertex[ 3 ] },
		{ vertex[ 0 ], vertex[ 3 ], vertex[ 2 ] }
	};
	for ( int i = 0; i < 2; i++ ) {
		model->addPolygon( quad_vertex[ i ][ 0 ], quad_vertex[ i ][ 1 ], quad_vertex[ i ][ 2 ] );
	}
}

void PlaneMaker::save( ) {
	for ( int i = 0; i < MAP_CHIP_NUM; i++ ) {
		std::string number = NUMBER[ i ];
		_plane[ i ]->save( "p_" + number + ".mdl" );
		_desert[ i ]->save( "d_" + number + ".mdl"  );
	}
}