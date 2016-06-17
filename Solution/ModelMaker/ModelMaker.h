#pragma once

#include "Task.h"
#include <string>

PTR( ModelMaker );

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
	enum STATE {
		STATE_VIEWER,
		STATE_LOAD,
		STATE_SAVE,
		STATE_MAX
	};

private:
	void load( );
	void save( );
private:
	STATE _state;
	ModePtr _model;
};

