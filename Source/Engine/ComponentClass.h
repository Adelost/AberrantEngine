#pragma once

#include <Engine/AbstractComponent.h>
#include <Engine/ComponentPool.h>

/// Template class all components should inherit from
/**
	It is used to manage class specific logic shared with all
    component such as generating a unique class id used to
	identify a component.
*/

template<class T>
class ComponentClass : public AbstractComponent
{
protected:
	ComponentClass() {}

public:
	static int typeId();
	static void setTypeId(int id);
	static void initClass()
	{

	}
	static T* create(Entity* entity)
	{
		int id = idFromEntity(entity);
		s_pool.add(id, T());
		return s_pool.valueFromId(id);
	}

	static T* get(int id)
	{
		return s_pool.valueFromId(id);
	}
	int entityId()
	{
		T* component = static_cast<T*>(this);
		return s_pool.id(*component);
	}

	#pragma region Iterator
public:
	class Iterator
	{
	public:
		typename ComponentPool<T>::Iterator begin()
		{
			return s_pool.begin();
		}
		typename ComponentPool<T>::Iterator end()
		{
			return s_pool.begin();
		}
	};
	static Iterator iterator;
	#pragma endregion

private:
	static int s_typeId;
	static ComponentPool<T> s_pool;
};

template<class T>
typename ComponentClass<T>::Iterator ComponentClass<T>::iterator;

template<class T>
int ComponentClass<T>::s_typeId = -1;

template<class T>
ComponentPool<T> ComponentClass<T>::s_pool;

template<class T>
int ComponentClass<T>::typeId()
{
	return s_typeId;
}

template<class T>
void ComponentClass<T>::setTypeId(int id)
{
	s_typeId = id;
}
