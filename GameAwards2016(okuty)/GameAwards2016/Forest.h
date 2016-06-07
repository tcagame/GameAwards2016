#pragma once
#include "Material.h"

class Forest : public Material {
public:
	Forest( MapPtr map );
	virtual ~Forest( );
public:
	void update( );
	bool install( const Coord& pos, unsigned char value );
	bool isTarget( ) const ;
	void setTargetFlag( bool info );
	void attack( int damage );
	bool isExist( ) const ;
private:
	void erase( );
private:
	bool _target_flag;
	bool erased;
	int _hp;
};

