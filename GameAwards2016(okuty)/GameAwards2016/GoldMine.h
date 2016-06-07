#pragma once
#include "Material.h"
#include "smart_ptr.h"

PTR( GoldMine );

class GoldMine : public Material {
public:
	GoldMine( MapPtr map );
	virtual ~GoldMine( );
public:
	void update( );
	bool install( const Coord& pos, unsigned char value );
	int getGold( int power );
	bool isExist( ) const;
	bool isTarget( ) const;
	void setTargetFlag( bool info );
private:
	int _gold;
	bool _target_flag;
};