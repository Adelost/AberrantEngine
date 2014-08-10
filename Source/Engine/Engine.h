#pragma once

#include "EntityManager.h"
#include "ComponentManager.h"

class Engine
{
public:
	static EntityManager entities;
	static ComponentManager components;
	template<class T> static void initComponent()
	{
		components.addType<T>();
	}
};