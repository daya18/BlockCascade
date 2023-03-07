#pragma once

#include "Object.hpp"

class ObjectGenerator
{
public:
	ObjectGenerator ( Grid const & grid )
		: grid ( grid )
	{
	}

	Object Generate () const
	{
		return { grid, objectTypeDefinitions[0] };
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

	Grid const & grid;
};