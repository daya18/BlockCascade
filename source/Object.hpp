#pragma once

#include "Core.hpp"
#include "Block.hpp"

using ObjectConfiguration = std::vector <sf::Vector2u>;

class Object
{
public:

	Object ( Grid const & grid, std::vector <ObjectConfiguration> const & orientationConfigurations )
		: gridIndex ( grid.GetCellCount ().x / 2, 0 )
	{
		for (auto const & blockGridIndex : orientationConfigurations[0])
		{
			blocks.push_back ( Block { grid, gridIndex + blockGridIndex } );
		}
	}

	void Move ( Directions direction )
	{
		if (stable) return;

		for (auto const & block : blocks)
		{
			auto [wallCollided, wallCollisionDirection] { block.CheckWallCollision () };

			if (wallCollided)
				if (wallCollisionDirection == direction)
					return;
		}


		for (auto & block : blocks)
			block.Move ( direction );
	}

	void Draw ( sf::RenderTarget & target )
	{
		for (auto const & block : blocks)
			block.Draw ( target );
	}

	void Update ( float delta )
	{
		if (!stable)
		{
			if ((nextDropIn -= delta) < 0.0f)
			{
				Move ( Directions::down );

				for (auto const & block : blocks)
				{
					auto [wallCollided, wallCollisionDirection] { block.CheckWallCollision () };

					if (wallCollided)
					{
						if (wallCollisionDirection == Directions::down)
							stable = true;

					}

				}

				nextDropIn = dropSpeed;
			}
		}
	}

private:
	/*void SetOrientation ( unsigned int orientation )
	{

	}*/

	using Configuration = char[3][3];

	const float dropSpeed { 0.5f };
	bool stable { false };
	float nextDropIn { dropSpeed };
	sf::Vector2u gridIndex;
	std::vector <Block> blocks;
};