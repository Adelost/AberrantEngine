#pragma once

#include <Engine/ComponentClass.h>
#include <GraphicsEngine/GraphicsEngine.h>


namespace Component
{
	template<class T>
	class Link
	{
	public:
		Link()
		{
		}
		Link(int id)
		{
		}
		
		template<class TT>
		Link(ComponentClass<TT>* hostComponent)
		{
			//int id = hostComponent->entityId();
			//m_index = hostComponent->get(id);
		}
		static void initClass(T* host)
		{
			m_host = host;
		}
		T* get()
		{
			//return &m_host->at(m_index);
			return new T();
		}
		T* operator->()
		{this
			return get();
		}

	private:
		int m_index;
		static T* m_host;
	};
}

template<class T>
T* Component::Link<T>::m_host;

namespace Component
{
	class Transform : public ComponentClass<Transform> {};
	class Arg : public ComponentClass<Arg> {};

	class Graphic : public ComponentClass<Graphic>
	{
	public:
		Graphic() : cArg(this), cTransform(this)
		{
		}

	public:
		Link<Arg> cArg;
		Link<Transform> cTransform;

		int id;
		
	};
}

namespace System
{
	class Graphic
	{
	public:
		Graphic()
		{
		}
		void update();
	private:
		GraphicsEngine graphicEngine;
	};

	static Graphic graphic;
}
