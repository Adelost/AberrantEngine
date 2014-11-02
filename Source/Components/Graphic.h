#pragma once

#include <Engine/ComponentBase.h>
//#include <GraphicsEngine/GraphicsEngine.h>


namespace Component
{
	template<class T>
	class Link
	{
	public:
		Link(int id)
		{
			//m_ptr = T->Create(id);
		}

		T* get()
		{
			return new T();
		}

		T* operator->()
		{
			return get();
		}

	private:
		static T* m_ptr;
	};
}

namespace Component
{
	class Transform : public ComponentBase < Transform > {};
	class Arg : public ComponentBase < Arg > {};

	class Graphic : public ComponentBase < Graphic >
	{
	public:
		Graphic(int id) : cTransform(id)
		{
			this->Create(id);
		}

	public:
		Link<Transform> cTransform;
	};
}

namespace System
{
	class Graphic
	{
	public:
		Graphic() {}
		void update();
	private:
		//GraphicsEngine graphicEngine;
	};

	static Graphic graphic;
}
