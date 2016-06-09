#include "Bases.h"
#include "Base.h"
#include "Map.h"

Bases::Bases( EnemiesPtr enemies, GuardiansPtr guardians ) {
	_enemies = enemies;
	_guardians = guardians;
}

Bases::~Bases( ) {
}

FacilityPtr Bases::createFacility( MapPtr map ) {
	return BasePtr( new Base( map, _guardians, _enemies ) );
}

void Bases::update( ) {
	for ( int i = 0; i < getSize( ); i++ ) {
		BasePtr base = std::dynamic_pointer_cast< Base >( get( i ) );
		base->update( );
	}
}
