#pragma once

#include "Task.h"
#include "mathmatics.h"
#include <string>

PTR( ModelMaker );
PTR( Model );

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
		STATE_TEXTURE,
		STATE_MAX
	};
private:
	void load( );
	void save( );
	void view( );
	void loadTexture( );
private:
	STATE _state;
	ModelPtr _model;
	int _texture;
};

