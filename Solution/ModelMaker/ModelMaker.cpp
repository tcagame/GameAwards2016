#include "ModelMaker.h"
#include "Framework.h"
#include "Keyboard.h"
#include "Parser.h"
#include "Model.h"

const int INPUT_X = 100;
const int INPUT_Y = 100;

ModelMakerPtr ModelMaker::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< ModelMaker >( fw->getTask( getTag( ) ) );
}

ModelMaker::ModelMaker( ) :
_state( STATE_VIEWER ) {
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
	case STATE_VIEWER:
		view( );
		break;
	}

	_state = STATE_VIEWER;
}

void ModelMaker::save( ) {
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
	FrameworkPtr fw = Framework::getInstance( );
	std::string filename = fw->inputString( INPUT_X, INPUT_Y );
	if ( filename.empty( ) ) {
		return;
	}

	if ( filename.find( ".x" ) != std::string::npos ) {
		ParserPtr Parser( new Parser );
		if ( !Parser->load( filename ) ) {
			return;
		}

		_model = Parser->makeModel( );
	}
	
	if ( filename.find( ".mdl" ) != std::string::npos ) {
		_model = ModelPtr( new Model );
		_model->load( filename );
	}
}

void ModelMaker::view( ) {
	KeyboardPtr keyboad = Keyboard::getTask( );
	if ( keyboad->isPushKey( "F1" ) ) {
		//_sta
	}
}