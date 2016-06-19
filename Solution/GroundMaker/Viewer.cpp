#include "Viewer.h"
#include "Framework.h"
#include "Model.h"
#include "Camera.h"

Viewer::Viewer( ) {
	_camera = CameraPtr( new Camera( ) );
	_model = ModelPtr( new Model( ) );
	_texture = LoadGraph( "GroudTexture.png" );
}

Viewer::~Viewer( ) {
}

void Viewer::setModel( ) {
	_model->load( "Map.mdl" );
}

void Viewer::draw( ) {
	_camera->update( );
	_model->draw( _texture );
	ScreenFlip( );
	ClearDrawScreen( );
}