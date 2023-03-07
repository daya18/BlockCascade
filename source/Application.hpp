#pragma once

#include "grid.hpp"
#include "World.hpp"

class Application
{
public:
	Application ();

	void Run ();
	void Exit () { exit = true; }

	Grid const & GetGrid () const { return grid; }
	sf::RenderWindow const & GetWindow () const { return window; }

private:
	void HandleEvents ();
	void Update ();
	void Render ();

	Grid grid ;
	sf::RenderWindow window;
	World world;
	bool exit { false };
};