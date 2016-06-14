#pragma once
#include "smart_ptr.h"
#include <string>

PTR( ModelMake );
PTR( ModelManager );

class ModelMake{
public:
	ModelMake( );
	virtual ~ModelMake( );
public:
	void setModel( );
	void saveModel( );
private:
	void setMountainModel( int mx, int my );
	void setPlainModel( int mx, int my );
	void setDesertModel( int mx, int my );
	void setRiverModel( int mx, int my );
	std::string getModelFile( int idx, unsigned char type );
	void setQuadranglePolygon( int sx, int sz, int u, int v );
private:
	ModelManagerPtr _model_manager;
};

