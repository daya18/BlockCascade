#pragma once

#include "SFML/System/Vector2.hpp"

class Grid
{
public:
	Grid ( float cellSize, sf::Vector2f const & cellCount, float gutterSize )
		: cellSize ( cellSize ), cellCount ( cellCount ), gutterSize ( gutterSize )
	{

	}

	sf::Vector2f GetSize () const
	{
		return {
			cellSize * cellCount.x + (gutterSize * (cellCount.x - 1)),
			cellSize * cellCount.y + (gutterSize * (cellCount.y - 1)),
		};
	};


	sf::Vector2f IndexToPosition ( sf::Vector2f index ) const {
		return {
			index.x * cellSize + gutterSize * index.x,
			index.y * cellSize + gutterSize * index.y
		};
	}

	sf::Vector2f PositionToIndex () const; // To be defined

	float GetCellSize () const { return cellSize; }
	sf::Vector2f const & GetCellCount () const { return cellCount; };

private:
	float cellSize;
	sf::Vector2f cellCount;
	float gutterSize;

};