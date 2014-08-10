#pragma once

#include <Utils/Introspect.h>

class Entity;

/// Allows access to logic shared with all components

class AbstractComponent : public Introspect
{
public:
	virtual void foo(){};

protected:
	static int idFromEntity(Entity* e);
};
