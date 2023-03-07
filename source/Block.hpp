#pragma once

#include "Grid.hpp"

class Block
{
public:
	Block ( Grid const & grid, sf::Vector2u gridIndex )
		:
		grid ( grid ),
		gridIndex ( gridIndex ),
		rect { { static_cast <float> (grid.GetCellSize ()), static_cast <float> (grid.GetCellSize ()) } }
	{
		rect.setPosition ( sf::Vector2f { grid.IndexToPosition ( gridIndex ) } );
		rect.setFillColor ( sf::Color::Green );
	}

	void Move ( Directions direction )
	{
		switch (direction)
		{
		case left:	--gridIndex.x; break;
		case right: ++gridIndex.x; break;
		case up:	--gridIndex.y; break;
		case down:	++gridIndex.y; break;
		}

		rect.setPosition ( sf::Vector2f { grid.IndexToPosition ( gridIndex ) } );
	}

	void Draw ( sf::RenderTarget & target ) const
	{
		target.draw ( rect );
	}

	struct CollisionResult { bool collided; Directions direction; };
	CollisionResult CheckWallCollision () const
	{
		if (rect.getPosition ().x <= 0.0f)
			return { true, Directions::left };
		else if (rect.getPosition ().x + rect.getSize ().x >= grid.GetSize ().x)
			return { true, Directions::right };
		else if (rect.getPosition ().y <= 0)
			return { true, Directions::up };
		else if (rect.getPosition ().y + rect.getSize ().y >= grid.GetSize ().y)
			return { true, Directions::down };

		return { false };
	}

private:
	Grid const & grid;
	sf::Vector2u gridIndex;
	sf::RectangleShape rect;
};