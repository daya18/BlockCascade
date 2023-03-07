#pragma once

#include "grid.hpp"
#include "World.hpp"
#include "ObjectGenerator.hpp"

class Application
{
public:
	Application ();

	void Run ();

	Grid const & GetGrid () const { return grid; }
	sf::RenderWindow const & GetWindow () const { return window; }
	ObjectGenerator const & GetObjectGenerator () const { return objectGenerator; }

private:
	void HandleEvents ();
	void Update ();
	void Render ();

	Grid grid { 30, { 15, 20 }, 1 };
	sf::RenderWindow window;
	ObjectGenerator objectGenerator;
	World world;
};