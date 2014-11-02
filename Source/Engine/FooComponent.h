#pragma once

#include <Engine/ComponentBase.h>

namespace Component
{
	/// Example of a created component, used for testing purposes

	class Foo : public ComponentBase<Foo>
	{
	public:
		int foo;
	};
}
