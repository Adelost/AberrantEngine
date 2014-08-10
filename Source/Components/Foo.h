#pragma once

#include "Engine/ComponentClass.h"

namespace Components
{
	struct Foo : public ComponentClass<Foo>
	{
	public:
		Foo()
		{
			flag = false;
			id = 42;
			health = 3.14f;
		}

	public:
		int id;
		bool flag;
		float health;

		INTROSPECT
			("Foo",
			MEMBER(Member::Int, id)
			MEMBER(Member::Bool, flag)
			MEMBER(Member::Float, health)
			)
	};

	struct Foo2 : public ComponentClass<Foo2>
	{
	public:
		Foo2() {}
		Foo2(int value)
		{
			m_value[0] = value;
		}
		int value()
		{
			return m_value[0];
		}
		int m_value[1];
	};
}

class Blarg : public Introspect
{
public:
	int id;
};

struct A : public ComponentClass<A>
{
	A()
	{
		m_value[0] = 0;
	}
	A(int value)
	{
		m_value[0] = value;
	}
	int value()
	{
		return m_value[0];
	}
	int m_value[1];
};
