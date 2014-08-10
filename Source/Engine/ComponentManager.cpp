#include "ComponentManager.h"
#include "Entity.h"

ComponentManager::ComponentManager()
{
}

ComponentManager::~ComponentManager()
{
	// Free memory
	for (AbstractComponentPool* s : storages)
		delete s;
}