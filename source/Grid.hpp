#pragma once

#include "SFML/System/Vector2.hpp"

class Grid
{
public:
	Grid ( unsigned int cellSize, sf::Vector2u const & cellCount, unsigned int gutterSize )
		: cellSize ( cellSize ), cellCount ( cellCount ), gutterSize ( gutterSize )
	{

	}

	sf::Vector2u GetSize () const
	{
		return {
			cellSize * cellCount.x + (gutterSize * (cellCount.x - 1)),
			cellSize * cellCount.y + (gutterSize * (cellCount.y - 1)),
		};
	};


	sf::Vector2u IndexToPosition ( sf::Vector2u index ) const {
		return {
			index.x * cellSize + gutterSize * index.x,
			index.y * cellSize + gutterSize * index.y
		};
	}

	sf::Vector2u PositionToIndex () const; // To be defined

	unsigned int GetCellSize () const { return cellSize; }
	sf::Vector2u const & GetCellCount () const { return cellCount; };

private:
	unsigned int cellSize;
	sf::Vector2u cellCount;
	unsigned int gutterSize;

};