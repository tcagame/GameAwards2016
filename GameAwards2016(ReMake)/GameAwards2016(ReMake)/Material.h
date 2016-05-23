#pragma once
#include "Object.h"
#include "smart_ptr.h"
#include "Chip.h"

PTR( Material );
PTR( Map );

class Material : public Object {
public:
	Material( MapPtr map, const int width, const int height );
	virtual ~Material();
public:
	bool install( const Coord& coord, CHIP_TYPE type, int value  );
private:
	const int _width;
	const int _height;
	MapPtr _map;
};

