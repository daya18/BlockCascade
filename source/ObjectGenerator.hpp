#pragma once

#include "Object.hpp"
#include "World.hpp"
#include "Application.hpp"

class ObjectGenerator
{
public:
	ObjectGenerator ()
	{
	}

	Object Generate ( World & world ) const
	{
		return Object { world, objectTypeDefinitions[0], sf::Vector2u { world.GetApplication ().GetGrid ().GetCellCount ().x / 2u, 0u } };
	}

private:

	std::vector <std::vector <ObjectConfiguration>> objectTypeDefinitions
	{
		// Square
		{
			{ { 0u, 0u }, { 1u, 0u }, { 1u, 1u }, { 0u, 1u } }
		},

		// Line
		{
			{ { 0u, 0u }, { 1u, 0u }, { 2u, 0u } },
			{ { 0u, 0u }, { 0u, 1u }, { 0u, 2u } }
		},

		// L
		{
			{ { 0u, 0u }, { 0u, 1u }, { 1u, 1u }, { 2u, 1u } }
		}
	};
};