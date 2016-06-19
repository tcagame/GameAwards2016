#pragma once

#include "smart_ptr.h"
#include "mathmatics.h"
#include <string>

PTR( Model );
PTR( ModelImpl );

class Model {
public:
	Model( );
	virtual ~Model( );
public:
	struct VERTEX {
		Vector pos;
		double u;
		double v;
		VERTEX( ) { }
		VERTEX( 
			Vector pos_,
			double u_,
			double v_ ) {
				pos = pos_;
				u = u_;
				v = v_;
		}
	};
public:
	void draw( int texture, bool trans = false ) const;
public:
	void alloc( int polygon_num );
	void translate( Vector move );
	void setPolygonNum( int num );
	void set( int n, VERTEX vertex ); // n * 3
	void load( std::string filename );
	void save( std::string filename );
private:
	ModelImplPtr _impl;
};

