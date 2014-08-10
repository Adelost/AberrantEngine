#include "EntityManager.h"

EntityManager::EntityManager()
{
	//Entity::s_entities = this;
}

Entity* EntityManager::create()
{
	int id = entities.nextIndex();
	static int uniqueId = 0;
	Entity e(id, uniqueId);
	uniqueId++;
	entities.add(e);

	return &entities[id];
}
