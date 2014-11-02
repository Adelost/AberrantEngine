#include <Engine/ComponentBase.h>

#include <Utils/Array.h>
#include <Utils/Algorithm.h>
#include <Utils/Console.h>
#include <Utils/Introspect.h>
#include <Utils/Math.h>
#include <Utils/Memory.h>
#include <Utils/Format.h>
#include <Utils/Random.h>
#include <Utils/Cast.h>


#include <iostream>
#include <vector>

using namespace ae;

void test();

int main()
{
	Memory::enableLeakDetection();

	test();

	Console::pressToContinue();

	return 0;
}

class Alpha : public ComponentBase<Alpha>
{
public:
	Alpha()
	{
	}
};

void test()
{
	Console::print() << "Test";

	Alpha a;



	/*for (auto cApple : Component::Apple::iterator)
	{
	int id = cApple->entityId();
	int size = sizeof(cApple);

	auto cBanana = Component::Banana::get(id);
	if (!cBanana)
	continue;
	auto cCitrus = Component::Citrus::get(id);
	if (!cCitrus)
	continue;
	}*/
}


