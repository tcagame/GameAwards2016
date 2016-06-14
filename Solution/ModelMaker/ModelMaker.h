#pragma once
#include "Task.h"
#include "ModelManager.h"
#include <string>

PTR( ModelMaker );

enum STATE {
	STATE_INPUT,
	STATE_LOAD,
	STATE_SAVE,
	STATE_END,
	STATE_MAX
};

class ModelMaker : public Task {
public:
	static ModelMakerPtr getTask( );
	static std::string getTag( ) { return "VIEWER"; }
public:
	ModelMaker( );
	virtual ~ModelMaker( );
public:
	void update( );
private:
	bool inputFileName( );
private:
	ModelManagerPtr _model_manager;
	STATE _state;
	std::string _file_name;
};

