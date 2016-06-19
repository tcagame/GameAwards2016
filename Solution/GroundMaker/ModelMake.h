#pragma once

#include "smart_ptr.h"
#include <string>

PTR( ModelMake );
PTR( Model );

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
	ModelPtr _model_moutain[ 16 ];
	ModelPtr _model_river[ 16 ];
	ModelPtr _model_desert[ 16 ];
	ModelPtr _model_plain[ 16 ];

	ModelPtr _model_ground;
};

