#include "Model.h"
#include "dxlib.h"

class ModelImpl {
public:
	VERTEX3D *_vertex;
	unsigned int _polygon_num;
};

Model::Model( ) {
	_impl = ModelImplPtr( new ModelImpl );

	_impl->_vertex = NULL;
	_impl->_polygon_num = 0;
}

Model::~Model( ) {
	if ( _impl->_vertex ) {
		delete [] _impl->_vertex;
	}
}

void Model::alloc( int polygon_num ) {
	_impl->_polygon_num = polygon_num;
	if ( _impl->_vertex != NULL ) {
		delete [] _impl->_vertex;
	}
	_impl->_vertex = new VERTEX3D[ polygon_num * 3 ];
}

void Model::setPolygonNum( int num ) {
	_impl->_polygon_num = num;
}

void Model::draw( int texture, bool trans ) const {
	int check = DrawPolygon3D( _impl->_vertex, _impl->_polygon_num, texture, trans ? TRUE : FALSE );
}

void Model::set( int n, VERTEX vertex ) {

	VERTEX3D vtx;
	vtx.pos = VGet( ( float )vertex.pos.x, ( float )vertex.pos.y, ( float )vertex.pos.z );
	vtx.norm = VGet( 0, 0, 0 );
	vtx.dif  = GetColorU8( 255, 255, 255, 255 );
	vtx.spc  = GetColorU8( 0, 0, 0, 0 );
	vtx.u    = ( float )vertex.u;
	vtx.v    = ( float )vertex.v;
	vtx.su   = 0.0f;
	vtx.sv   = 0.0f;

	_impl->_vertex[ n ] = vtx;
}

bool Model::load( std::string filename ) {
	int fh = FileRead_open( filename.c_str( ) );
	if ( fh <= 0 ) {
		return false;
	}

	unsigned int polygon_num;
	FileRead_read( &polygon_num, sizeof( unsigned int ), fh );
	
	alloc( polygon_num );

	FileRead_read( _impl->_vertex, sizeof( DxLib::VERTEX3D ) * ( polygon_num * 3 ), fh );

	FileRead_close( fh );
	return true;
}

void Model::save( std::string filename ) {
	FILE *fp;
	errno_t err = fopen_s( &fp, filename.c_str( ), "wb" );
	if ( err != 0 ) {
		return;
	}
	
	fwrite( &_impl->_polygon_num, sizeof( unsigned int ), 1, fp );
	fwrite( _impl->_vertex, sizeof( DxLib::VERTEX3D ) * ( _impl->_polygon_num * 3 ), 1, fp );

	fclose( fp );
}

void Model::multiply( Matrix matrix ) {
	int count = ( int )_impl->_polygon_num * 3;
	for ( int i = 0; i < count; i++ ) {
		Vector pos(
			_impl->_vertex[ i ].pos.x,
			_impl->_vertex[ i ].pos.y,
			_impl->_vertex[ i ].pos.z );
		pos = matrix.multiply( pos );
		_impl->_vertex[ i ].pos = VGet( ( float )pos.x, ( float )pos.y, ( float )pos.z );
	}
}

void Model::addPolygon( VERTEX vertex1, VERTEX vertex2, VERTEX vertex3 ) {
	int idx = _impl->_polygon_num * 3;
	int vertex_num =  ( _impl->_polygon_num + 1 ) * 3;
	_impl->_polygon_num++;
	_impl->_vertex = ( VERTEX3D* )realloc( _impl->_vertex, sizeof( VERTEX3D ) );

	set( idx + 0, vertex1 );
	set( idx + 1, vertex2 );
	set( idx + 2, vertex3 );
}

void Model::mergeModel( ModelConstPtr model ) {
	if ( model == NULL ) {
		return;
	}

	ModelImplConstPtr merge_impl = model->getModelImpl( );
	int polygon_num = _impl->_polygon_num + merge_impl->_polygon_num;
	VERTEX3D* vertex = new VERTEX3D[ sizeof( VERTEX3D ) * polygon_num * 3 ];

	// this のモデルをコピー
	for ( int i = 0; i < ( int )_impl->_polygon_num * 3; i++ ) {
		vertex[ i ] = _impl->_vertex[ i ];
	}
	// modelのモデルをコピー
	for ( int i = 0; i < ( int )merge_impl->_polygon_num * 3; i++ ) {
		int idx = _impl->_polygon_num * 3 + i;
		vertex[ idx ] = merge_impl->_vertex[ i ];
	}

	if ( _impl->_vertex ) {
		delete [] _impl->_vertex;
	}
	_impl->_vertex = vertex;
	_impl->_polygon_num = polygon_num;
}

ModelImplConstPtr Model::getModelImpl( ) const {
	return _impl;
}