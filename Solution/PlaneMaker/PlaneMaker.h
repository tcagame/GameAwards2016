#pragma once
#include "smart_ptr.h"

PTR( Model );
PTR( PlaneMaker );

class PlaneMaker {
public:
	PlaneMaker( );
	virtual ~PlaneMaker( );
private:
	void makeModel( );
	void makePlaneModel( int id );
	void makeDesertModel( int id );
	void setQuadranglePolygon( int sx, int sy, int u, int v, ModelPtr model );
	void save( );
private:
	static const int MAP_CHIP_NUM = 16;
	ModelPtr _plane[ MAP_CHIP_NUM ];
	ModelPtr _desert[ MAP_CHIP_NUM ];
};

