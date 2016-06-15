#include "Viewer.h"
#include "Framework.h"
#include "Model.h"
#include "Camera.h"
#include "ModelManager.h"

Viewer::Viewer( ) {
	_camera = CameraPtr( new Camera( ) );
	_model_manager = ModelManagerPtr( new ModelManager( ) );
	_model = ModelPtr( new Model( ) );
}

Viewer::~Viewer( ) {
}

void Viewer::setModel( ) {
	_model_manager->loadModelData( "../resource3D/model(dummy)/Map.mdl" );
	_model->alloc( _model_manager->getVertexNum( ) / 3 );
	for ( int i = 0; i < _model_manager->getVertexNum( ); i++ ) {
		_model->set( i, _model_manager->getVERTEX( i ) );
	}
}

void Viewer::draw( ) {
	_camera->update( );
	_model->draw( );
	ScreenFlip( );
	ClearDrawScreen( );
}