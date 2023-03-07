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

	Application & GetApplication () { return application; }
	std::vector <Object> & GetObjects () { return objects; }

private:
	void SpawnObject ();

	Application & application;
	Object object;
	float dropSpeed { 0.7f };
	float nextDropIn { dropSpeed };
	std::vector <Object> objects;

	static std::vector <std::vector <ObjectConfiguration>> objectTypeDefinitions;
};