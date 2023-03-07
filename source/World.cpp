#include "World.hpp"
#include <iostream>

#include "Application.hpp"

std::vector <std::vector <ObjectConfiguration>> World::objectTypeDefinitions
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
		{ { 0u, 0u }, { 0u, 1u }, { 1u, 1u }, { 2u, 1u } },
		{ { 2u, 0u }, { 1u, 0u }, { 1u, 1u }, { 1u, 2u } },
		{ { 0u, 1u }, { 1u, 1u }, { 2u, 1u }, { 2u, 2u } },
		{ { 1u, 0u }, { 1u, 1u }, { 1u, 2u }, { 0u, 2u } },
	}
	// T
};


World::World ( Application & application )
	:
	application ( application )
{
	SpawnObject ();
	//Grid index for center spawning:
	
	//this->object = application.GetObjectGenerator ().Generate ( *this );

}

void World::HandleEvent ( sf::Event const & event )
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		switch (event.key.code)
		{
		case sf::Keyboard::Right: object.Move ( Directions::right ); break;
		case sf::Keyboard::Left: object.Move ( Directions::left ); break;
		case sf::Keyboard::Space: break;
		}
		break;
	}
}

void World::Draw ( sf::RenderTarget & target )
{
	object.Draw ( target );

	for (auto & object : objects)
		object.Draw ( target );
}

void World::Update ( float delta )
{
	object.Update ( delta );

	if ( ( nextDropIn -= delta ) < 0.0f)
	{
		if ( object.CheckCollision ( Directions::down ) )
		{
			objects.push_back ( object );
			SpawnObject ();
		}
		else
		{
			object.Move ( Directions::down );

		}

		nextDropIn = dropSpeed;
	}
}

void World::SpawnObject ()
{
	object = { *this, objectTypeDefinitions[0], { GetApplication ().GetGrid ().GetCellCount ().x / 2.0f, 0.0f } };
}