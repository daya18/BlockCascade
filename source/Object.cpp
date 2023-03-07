#include "Object.hpp"

#include <iostream>

#include "World.hpp"
#include "Application.hpp"

Object::Object ( 
	World & world, 
	std::vector <ObjectConfiguration> const & orientationConfigurations, 
	sf::Vector2u const & gridIndex 
)
	: gridIndex ( gridIndex )
{
	for (auto const & blockGridIndex : orientationConfigurations[0])
	{
		blocks.push_back ( Block { world, gridIndex + blockGridIndex } );
	}
}

void Object::Move ( Directions direction )
{
	//if (stable) return;
	
	for (auto const & block : blocks )
	{
		if (block.CheckCollision ( direction ) )
			return;
	}


	for (auto & block : blocks)
		block.Move ( direction );
}

void Object::Draw ( sf::RenderTarget & target )
{
	for (auto const & block : blocks)
		block.Draw ( target );
}

void Object::Update ( float delta )
{
	for (auto & block : blocks)
		block.Update ();
}

bool Object::CheckCollision ( Directions direction ) const
{
	for (auto const & block : blocks)
	{
		if (block.CheckCollision ( direction ))
		{
			return true;
		}
	}

	return false;
}