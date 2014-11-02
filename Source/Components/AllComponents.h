#pragma once

#include "Graphic.h"
#include "Foo.h"

//! Test components.
namespace Component
{
	class Apple : public ComponentBase < Apple >
	{
	public:
		int id;
	};
	class Banana : public ComponentBase < Banana > {};
	class Citrus : public ComponentBase < Citrus > {};
	class Durian : public ComponentBase < Durian > {};
	class Eggplant : public ComponentBase < Eggplant > {};
	class Fig : public ComponentBase < Fig > {};
	class Grapes : public ComponentBase < Grapes > {};
}

namespace Component
{
	class Input : public ComponentBase < Input >
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


