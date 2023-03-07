#pragma once

#include "Object.hpp"

class Application;

class World
{
public:
	World ( Application & application );

	void HandleEvent ( sf::Event const & event );
	void Draw ( sf::RenderTarget & target );
	void Update ( float delta );

private:
	Object object;

};