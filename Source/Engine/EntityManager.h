#pragma once

#include "Entity.h"
#include <Utils/PoolArray.h>

class EntityManager
{
public:
	EntityManager();
	Entity* create();

private:
	PoolArray<Entity> entities;
};