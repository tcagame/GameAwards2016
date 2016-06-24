#include "ModelMaker.h"
#include "Framework.h"
#include "Keyboard.h"
#include "Parser.h"
#include "Model.h"
#include "DxLib.h"

const int INPUT_X = 100;
const int INPUT_Y = 100;

ModelMakerPtr ModelMaker::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< ModelMaker >( fw->getTask( getTag( ) ) );
}

ModelMaker::ModelMaker( ) :
_state( STATE_VIEWER )
, _texture( DX_NONE_GRAPH ) {
}

ModelMaker::~ModelMaker( ) {
}

void ModelMaker::update( ) {
	switch ( _state ) {
	case STATE_LOAD:
		load( );
		break;
	case STATE_SAVE:
		save( );
		break;
	case STATE_TEXTURE:
		loadTexture( );
		break;
	case STATE_VIEWER:
		view( );
		break;
	}
}

void ModelMaker::save( ) {
	_state = STATE_VIEWER;

	if ( !_model ) {
		return;
	}

	FrameworkPtr fw = Framework::getInstance( );
	std::string filename = fw->inputString( INPUT_X, INPUT_Y );
	if ( filename.empty( ) ) {
		return;
	}
	
	if ( filename.find( ".mdl" ) == std::string::npos ) {
		filename += ".mdl";
	}

	_model->save( filename );
}

void ModelMaker::load( ) {
	_state = STATE_VIEWER;

	FrameworkPtr fw = Framework::getInstance( );
	std::string filename = fw->inputString( INPUT_X, INPUT_Y );
	if ( filename.empty( ) ) {
		return;
	}

	if ( filename.find( ".x" ) != std::string::npos ) {
		ParserPtr parser( new Parser );
		_model = parser->makeModel( filename );
	}
	
	if ( filename.find( ".mdl" ) != std::string::npos ) {
		_model = ModelPtr( new Model );
		if ( !_model->load( filename ) ) {
			_model.reset( );
		}
	}
}

void ModelMaker::view( ) {
	KeyboardPtr keyboard = Keyboard::getTask( );

	if ( keyboard->isPushKey( "F1" ) ) {
		_state = STATE_LOAD;
	}
	if ( keyboard->isPushKey( "F2" ) ) {
		_state = STATE_TEXTURE;
	}
	if ( keyboard->isPushKey( "F5" ) ) {
		_state = STATE_SAVE;
	}
	
	if ( keyboard->isPushKey( "X" ) ) {
		Matrix matrix = Matrix::makeTransformRotation( Vector( 1, 0, 0 ), PI2 / 4 ); // XŽ²‚É90“x‰ñ“]
		_model->multiply( matrix );
	}

	if ( keyboard->isPushKey( "Y" ) ) {
		Matrix matrix = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), PI2 / 4 ); // YŽ²‚É90“x‰ñ“]
		_model->multiply( matrix );
	}

	if ( keyboard->isPushKey( "Z" ) ) {
		Matrix matrix = Matrix::makeTransformRotation( Vector( 0, 0, 1 ), PI2 / 4 ); // ZŽ²‚É90“x‰ñ“]
		_model->multiply( matrix );
	}
	
	if ( keyboard->isPushKey( "A" ) ) {
		Vector max = _model->getMaxPoint( );
		double length = max.x;
		if ( length < max.y ) {
			length = max.y;
		}
		double scale = 0.5 / length;
		Matrix matrix = Matrix::makeTransformScaling( Vector( scale, scale, scale ) ); // ZŽ²‚É90“x‰ñ“]
		_model->multiply( matrix );
	}



	ScreenFlip( );
	ClearDrawScreen( );
	if ( _model ) {
		_model->draw( _texture );
	}
}

void ModelMaker::loadTexture( ) {
	_state = STATE_VIEWER;
	if ( _texture != DX_NONE_GRAPH ) {
		DeleteGraph( _texture );
		_texture = DX_NONE_GRAPH;
	}

	FrameworkPtr fw = Framework::getInstance( );
	std::string filename = fw->inputString( INPUT_X, INPUT_Y );
	if ( filename.empty( ) ) {
		return;
	}
	_texture = LoadGraph( filename.c_str( ) );
	if ( _texture < 0 ) {
		_texture = DX_NONE_GRAPH;
	}
}
