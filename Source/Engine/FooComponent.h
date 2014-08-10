#pragma once

#include <Engine/ComponentClass.h>

namespace Component
{
	/// Example of a created component, used for testing purposes

	class Foo : public ComponentClass<Foo>
	{
	public:
		int foo;
	};
}
