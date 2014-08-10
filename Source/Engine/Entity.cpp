#include "EntityManager.h"

#include <Utils/StaticCall.h>
#include "Engine.h"

ComponentManager* Entity::s_components;

STATIC_CALL(Entity::staticInit();)

Entity* Entity::create()
{
	return Engine::entities.create();
}

void Entity::staticInit()
{
	s_components = &Engine::components;
}

Entity::Entity()
{

}

Entity::Entity(int id, int uniqueId)
{
	m_id = id;
	//m_uniqueId = uniqueId;
}

int Entity::id()
{
	return m_id;
}
