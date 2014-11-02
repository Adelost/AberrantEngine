#pragma once

#include "Entity.h"
//#include <Utils/NativePoolArray.h>

class EntityManager
{
public:
	EntityManager();
	Entity* create();

private:
	//NativePoolArray<Entity> entities;
};