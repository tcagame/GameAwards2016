#include "Viewer.h"
#include "Framework.h"
#include "Model.h"
#include "DxLib.h"

Viewer::Viewer( ) {
	_model = ModelPtr( new Model( ) );
	_texture = LoadGraph( "GroudTexture.png" );
}

Viewer::~Viewer( ) {
}

void Viewer::setModel( ) {
	_model->load( "Map.mdl" );
}

void Viewer::draw( ) {
	_model->draw( _texture );
	ScreenFlip( );
	ClearDrawScreen( );
}