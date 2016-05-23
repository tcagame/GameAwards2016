#pragma once
#include "Material.h"

class Forest : public Material {
public:
	Forest( MapPtr map );
	virtual ~Forest( );
public:
	void update( );
	bool install( const Coord& pos, unsigned char value );
	bool isTarget( );
	void setTargetFlag( bool info );
private:
	bool _target_flag;
};

