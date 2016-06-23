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
	KeyboardPtr keyboad = Keyboard::getTask( );
	if ( keyboad->isPushKey( "F1" ) ) {
		_state = STATE_LOAD;
	}
	if ( keyboad->isPushKey( "F2" ) ) {
		_state = STATE_TEXTURE;
	}
	if ( keyboad->isPushKey( "F5" ) ) {
		_state = STATE_SAVE;
	}

	if ( _model ) {
		_model->draw( _texture );
	}
	ScreenFlip( );
	ClearDrawScreen( );
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

void ModelMaker::transferModel( Matrix matrix ) {
	_model->multiply( matrix );
}