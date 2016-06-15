#include "ModelMaker.h"
#include "Framework.h"
#include "ModelManager.h"
#include "DxLib.h"

const int INPUT_X = 100;
const int INPUT_Y = 100;
const int MAX_STRING = 1024;
const char DIRECTORY[] = "../resource3D/model(dummy)/";


ModelMakerPtr ModelMaker::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< ModelMaker >( fw->getTask( getTag( ) ) );
}

ModelMaker::ModelMaker( ) {
	_model_manager = ModelManagerPtr( new ModelManager( ) );
}

ModelMaker::~ModelMaker( ) {
}

void ModelMaker::update( ) {
	switch ( _state ) {
		case STATE_INPUT:
			if ( inputFileName( ) ) {
				_state = STATE_LOAD;
			}
			break;
		case STATE_LOAD:
			if ( _file_name.find( ".x" ) == std::string::npos ) {
				_file_name = _file_name + ".x";
			}
			_model_manager->loadModelData( _file_name.c_str( ) );
			_state = STATE_SAVE;
			break;
		case STATE_SAVE:
			if ( _file_name.find( ".x" ) != std::string::npos ) {
				_file_name = _file_name.substr( 0, _file_name.find( ".x" ) );
			}
			_file_name = _file_name + ".mdl";
			_model_manager->saveModelData( _file_name.c_str( ) );
			_state = STATE_END;
			break;
		case STATE_END:
			break;
	}
}

bool ModelMaker::inputFileName( ) {
	char buf[ MAX_STRING ];
	bool result = ( KeyInputString( INPUT_X, INPUT_Y, MAX_STRING, buf, TRUE ) == TRUE );
	if ( result ) {
		_file_name = buf;
		_file_name = DIRECTORY + _file_name;
	}
	return result;
}
