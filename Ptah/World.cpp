#include "World.h"
#include "Entities/EntityManager.h"

Ptah::World::World() : entity_manager_(new EntityManager(*this))
{
}

Ptah::World::~World()
{
	delete entity_manager_;
}