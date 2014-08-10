#pragma once

#include "Graphic.h"
#include "Foo.h"

// Test components

namespace Component
{
	class Apple : public ComponentClass<Apple>
	{
	public:
		int id;
	};
	class Banana : public ComponentClass<Banana> {};
	class Citrus : public ComponentClass<Citrus> {};
	class Durian : public ComponentClass<Durian> {};
	class Eggplant : public ComponentClass<Eggplant> {};
	class Fig : public ComponentClass<Fig> {};
	class Grapes : public ComponentClass<Grapes> {};
}


namespace Component
{
	class Input : public ComponentClass<Input>
	{
	public:
		Input()
		{
			button("Forward");
		}
		void button(std::string button)
		{
			button;
		}
	};
}


