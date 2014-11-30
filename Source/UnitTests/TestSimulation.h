#pragma once

#include "Catch.h"

using namespace ae;


#include <Engine/Entity.h>
#include <Components/Test.h>

TEST_CASE("Entities and Components")
{
	Entity* e = Entity::Create();

	auto cAlpha = com::Alpha::Create(e);
	auto cBeta = com::Beta::Create(e);
	com::Beta::Create(e);

	auto it = com::Beta::Iterator();

	int i = 0;
	for (auto b : com::Beta::Iterator())
	{
		b->b = i;
		i++;
	}

	int total = 0;
	for (auto cBeta : com::Beta::Iterator())
	{
		cBeta->cAlpha->a;	
	}
}

#include <Simulation/Simulation.h>
#include <Components/Input.h>

TEST_CASE("Simulation")
{
	Simulation simulation;
	simulation.update();

	SECTION("Input")
	{
		auto arg = sys::Input;

		sys::Button.set("A", true);

		REQUIRE(sys::Button.isDown("A"));
		REQUIRE(sys::Button.down("A"));
		REQUIRE(sys::Button.up("A") == false);
		
		sys::Button.set("A", false);

		REQUIRE(sys::Button.isDown("A") == false);
		REQUIRE(sys::Button.down("A"));
		REQUIRE(sys::Button.up("A"));

		sys::Button.update();

		REQUIRE(sys::Button.isDown("A") == false);
		REQUIRE(sys::Button.down("A") == false);
		REQUIRE(sys::Button.up("A") == false);;
	}
}

TEST_CASE("Systems")
{
}

TEST_CASE("Entity Hierarchy")
{
	Entity* e = Entity::Create();

	com::Beta::Create(e);

	Entity* ee = Entity::Create();
	com::Beta::Create(ee);
}
