//#include "FileOpener.h"

#include <Engine/Engine.h>
#include <Components/Foo.h>
#include <Utils/PoolArray.h>
#include <Utils/PoolList.h>
#include <Utils/Array.h>
#include <Utils/DebugOnly.h>
#include <Utils/StopWatch.h>
#include <Utils/StringConvert.h>

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>

//1 4
//4 16
//64 256
struct Abc
{
	int data[4];
};

void testAlloc()
{
	StopWatch startTimer;
	StopWatch timer;
	//FileOpener fileAdd("xAdd64.txt");
	//FileOpener fileRem("xRem16.txt");

	Array<Abc> arr;

	int count = 0;
	while (count <= 100000)
	{
		std::cout << count << std::endl;

		// Add
		timer.start();
		for (int i = 0; i < count; i++)
		{
			arr.addEmpty();
		}
		timer.pause();

		std::string strAdd = StringConvert::toString(arr.count()) + " " +
		                     StringConvert::toString(timer.timeMs()) + "\n";
		//fileAdd.write(strAdd);

// 		// Remove
// 		timer.start();
// 		for (auto& a : arr)
// 			delete a;
// 		timer.pause();
//
// 		std::string strRem= StringConvert::toString(arr.count()) + " " + StringConvert::toString(timer.timeMs()) + "\n";
// 		fileRem.write(strRem);

		count += 5000;
	}
}
void testEngine()
{
	//Engine::initComponent<Component::Foo>();
	//Engine::initComponent<Component::Foo2>();
	Engine::initComponent<A>();
}

void testPerformance();


int main()
{
	// Detect memory leaks
	DEBUG_ONLY(_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);)

	//FileOpener fileAdd("xAdd64.txt");

	const int MAX_ELEMENTS = 100000;
	int solid[MAX_ELEMENTS];

	testEngine();
	testPerformance();
	//testAlloc();

	// Ending
	std::cout << "Press any key to continue . . . ";
	getchar();
	return solid[0];
}

void testPerformance()
{
	// Make sure code is only run in debug
#ifdef _DEBUG
	const int MAX_ELEMENTS = 5;
	const int LOOP = 2;
#else
	const int MAX_ELEMENTS = 100000;
	const int LOOP = 1000;
#endif


	StopWatch watch;
	int total;
	int time;

	// Implementation HERE
	//A solid[MAX_ELEMENTS];
	std::vector<A> vec;
	Array<A> arr;
	PoolArray<A> pool;
	std::list<A> stdList;
	PoolList<A> poolList;
	ComponentPool<A> com;
	Array<Entity> entities;


	// Init
	for (int i = 0; i < MAX_ELEMENTS; i++)
	{
		/*  vec.push_back(i);
		    arr.add(i);
		    pool.add(i);
		    stdList.push_back(i);
		    poolList.add(i);

		    com.add(i, i);

		    Entity* e = Entity::create();
		    e->addComponent(A(i));*/

	}

	// Test array iterator
// 	total = 0;
// 	watch.start();
// 	for (int i = 0; i < LOOP; i++)
// 	{
// 		for (int j = 0; j < MAX_ELEMENTS; j++)
// 		{
// 			solid[j] = j;
// 		}
// 	}
// 	std::cout << "SolidAdd: " << watch.timeMs() << std::endl;
// 	std::cout << total << std::endl;

	std::map <std::string, int> button;

	for (int i = 0; i < 10; i++)
	{
		button["" + std::to_string(i)] = i;
	}
	button["Left"] = 41;
	button["Right"] = 42;
	for (auto iterator = button.begin(); iterator != button.end(); iterator++)
	{
		std::cout << iterator->first << std::endl;
		// iterator->first = key
		// iterator->second = value
		// Repeat if you also want to iterate through the second map.
	}
	

	total = 0;
	watch.start();
	for (int i = 0; i < LOOP; i++)
	{
		vec.clear();
		for (int j = 0; j < MAX_ELEMENTS; j++)
		{
			if (button["Left"] == 43)
				vec.push_back(j);
		}
	}
	std::cout << "VecAdd: " << watch.timeMs() << std::endl;
	std::cout << total << std::endl;

	return;


	total = 0;
	watch.start();
	for (int i = 0; i < LOOP; i++)
	{
		arr.clear();
		for (int j = 0; j < MAX_ELEMENTS; j++)
		{
			arr.add(j);
		}
	}
	std::cout << "ArrAdd: " << watch.timeMs() << std::endl;
	std::cout << total << std::endl;

	total = 0;
	watch.start();
	for (int i = 0; i < LOOP; i++)
	{
		pool.clear();
		for (int j = 0; j < MAX_ELEMENTS; j++)
		{
			pool.add(j);
		}
	}
	std::cout << "PoolAdd: " << watch.timeMs() << std::endl;
	std::cout << total << std::endl;

	total = 0;
	watch.start();
	for (int i = 0; i < LOOP; i++)
	{
		poolList.clear();
		for (int j = 0; j < MAX_ELEMENTS; j++)
		{
			poolList.add(j);
		}
	}
	std::cout << "PoolList: " << watch.timeMs() << std::endl;
	std::cout << total << std::endl;


	total = 0;
	watch.start();
	for (int i = 0; i < LOOP; i++)
	{
		com.clear();
		for (int j = 0; j < MAX_ELEMENTS; j++)
		{
			com.add(j, j);
		}
	}
	std::cout << "ComAdd: " << watch.timeMs() << std::endl;
	std::cout << total << std::endl;

	//////////////////////////////////////////////////////////////////////////

// 	total = 0;
// 	watch.start();
// 	for (int i = 0; i < LOOP; i++)
// 	{
// 		for (int j = 0; j < sizeof(solid) / sizeof(solid[0]); j++)
// 		{
// 			total += solid[j].value();
// 		}
// 	}
// 	std::cout << "solid: " << watch.timeMs() << std::endl;
// 	std::cout << total << std::endl;

	total = 0;
	watch.start();
	for (int i = 0; i < LOOP; i++)
	{
		for (auto& v : vec)
			total += v.value();
	}
	std::cout << "vec: " << watch.timeMs() << std::endl;
	std::cout << total << std::endl;

	total = 0;
	watch.start();
	for (int i = 0; i < LOOP; i++)
	{
		for (auto& v : arr)
			total += v.value();
	}
	std::cout << "arr: " << watch.timeMs() << std::endl;
	std::cout << total << std::endl;

	total = 0;
	watch.start();
	for (int i = 0; i < LOOP; i++)
	{
		for (auto& v : pool)
		{
			total += v.value();
		}
	}
	time = watch.timeMs();
	std::cout << "pool: " << time << std::endl;
	std::cout << total << std::endl;

	total = 0;
	watch.start();
	for (int i = 0; i < LOOP; i++)
	{
		for (auto& a : stdList)
		{
			total += a.value();
		}
	}
	time = watch.timeMs();
	std::cout << "stdList: " << time << std::endl;
	std::cout << total << std::endl;

	total = 0;
	watch.start();
	for (int i = 0; i < LOOP; i++)
	{
		auto it = poolList.iterator();
		while (it.hasNext())
		{
			total += it.next().value();
		}
	}
	time = watch.timeMs();
	std::cout << "poolList: " << time << std::endl;
	std::cout << total << std::endl;

	total = 0;
	watch.start();
// 	for (int i = 0; i < LOOP; i++)
// 	{
// 		for (auto& v : com)
// 		{
// 			total += v.value();
// 		}
// 	}
	time = watch.timeMs();
	std::cout << "com: " << time << std::endl;
	std::cout << total << std::endl;

	total = 0;
	watch.start();
	for (int i = 0; i < LOOP; i++)
	{
		for (int j = 0; j < MAX_ELEMENTS; j++)
		{
			total += Engine::components.get<A>(j)->value();
		}
	}
	time = watch.timeMs();
	std::cout << "ent: " << time << std::endl;
	std::cout << total << std::endl;

	total = 0;
	watch.start();
	for (int i = 0; i < LOOP; i++)
	{
		for (Entity& e : entities)
		{
			total += e.component<A>()->value();
		}
	}
	time = watch.timeMs();
	std::cout << "ent2: " << time << std::endl;
	std::cout << total << std::endl;

	total = 0;
	watch.start();
	for (int i = 0; i < LOOP; i++)
	{
		for (Entity& e : entities)
		{
			total += com.valueFromId(e.id())->value();
		}
	}
	time = watch.timeMs();
	std::cout << "ent3: " << time << std::endl;
	std::cout << total << std::endl;


	time = watch.timeMs();
	std::cout << "ent4: " << time << std::endl;
	std::cout << total << std::endl;
}