#include "Block.hpp"

#include "Application.hpp"
#include "World.hpp"

#include <iostream>

Block::Block ( World & world, sf::Vector2u gridIndex )
:
	world ( & world ),
	grid ( & world.GetApplication ().GetGrid () ),
	gridIndex ( gridIndex ),
	rect { { static_cast <float> (grid->GetCellSize ()), static_cast <float> (grid->GetCellSize ()) } }
{
	rect.setPosition ( sf::Vector2f { grid->IndexToPosition ( gridIndex ) } );
	rect.setFillColor ( sf::Color::Green );
}

void Block::Move ( Directions direction )
{
	switch (direction)
	{
	case left:	--gridIndex.x; break;
	case right: ++gridIndex.x; break;
	case up:	--gridIndex.y; break;
	case down:	++gridIndex.y; break;
	}

	rect.setPosition ( sf::Vector2f { grid->IndexToPosition ( gridIndex ) } );
}

void Block::Draw ( sf::RenderTarget & target ) const
{
	target.draw ( rect );
}

void Block::Update ()
{
	UpdateCollisionState ();
}

bool Block::CheckCollision ( Directions direction ) const
{
	return wallCollisionState.at(direction) || blockCollisionState.at(direction);
}

std::unordered_map <Directions, float> Block::GetEdgesInWorldSpace ()
{
	return 
	{
		{ Directions::left,		rect.getPosition ().x },
		{ Directions::up,		rect.getPosition ().y },
		{ Directions::right,	rect.getPosition ().x + rect.getSize ().x },
		{ Directions::down,		rect.getPosition ().y + rect.getSize ().y }
	};
}

bool Block::CheckBlockCollision ( Directions direction )
{
	for (auto & object : world->GetObjects ())
	{
		for (auto & block : object.GetBlocks ())
		{
			switch (direction)
			{
			case Directions::left:	
				if ( gridIndex == block.gridIndex + sf::Vector2u { 1u, 0u }) return true;
			case Directions::right: 
				if (gridIndex == block.gridIndex - sf::Vector2u { 1u, 0u }) return true;
			case Directions::up:
				if (gridIndex == block.gridIndex + sf::Vector2u { 0u, 1u }) return true;
			case Directions::down:
				if (gridIndex == block.gridIndex - sf::Vector2u { 0u, 1u }) return true;
			}
		}
	}
	return false;
}

void Block::UpdateCollisionState ()
{
	// Wall Collision State
	wallCollisionState [Directions::left]	=	rect.getPosition ().x <= 0.0f;
	wallCollisionState [Directions::right]	=	rect.getPosition ().x + rect.getSize ().x >= grid->GetSize ().x;
	wallCollisionState [Directions::up]		=	rect.getPosition ().y <= 0;
	wallCollisionState [Directions::down]	=	rect.getPosition ().y + rect.getSize ().y >= grid->GetSize ().y;
	
	// Block Collision State
	blockCollisionState [Directions::left]		=	CheckBlockCollision ( Directions::left );
	blockCollisionState [Directions::right]		=	CheckBlockCollision ( Directions::right );
	blockCollisionState [Directions::up]		=	CheckBlockCollision ( Directions::up );
	blockCollisionState [Directions::down]		=	CheckBlockCollision ( Directions::down );
}