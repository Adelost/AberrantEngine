#include "AbstractComponent.h"

#include "Entity.h"



int AbstractComponent::idFromEntity(Entity* e)
{
	return e->id();
}
