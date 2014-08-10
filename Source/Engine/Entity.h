#pragma once

#include "ComponentManager.h"

class EntityManager;

/// Standard representation of a game entity / game object

class Entity
{
public:
	Entity();
	Entity(int id, int uniqueId);
	
	/// Add component
	template<class T> void addComponent(const T& component);
	/// Remove component
	template<class T> void removeComponent();
	void remove() {}
	void clone() {}

	/// Get component
	template<class T> T* component();
	int id();

	static void staticInit();
	static Entity* create();

public:
	int m_id;

	static ComponentManager* s_components;
};

template<class T>
T* Entity::component()
{
	return s_components->get<T>(m_id);
}

template<class T>
void Entity::addComponent(const T& component)
{
	s_components->add<T>(m_id, component);
}

template<class T>
void Entity::removeComponent()
{
	s_components->remove<T>(m_id);
}
