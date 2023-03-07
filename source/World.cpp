#include "World.hpp"

#include "Application.hpp"

World::World ( Application & application )
	: object { application.GetObjectGenerator ().Generate () }
{

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
		}
		break;
	}
}

void World::Draw ( sf::RenderTarget & target )
{
	object.Draw ( target );
}

void World::Update ( float delta )
{
	object.Update ( delta );
}