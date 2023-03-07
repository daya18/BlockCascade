#pragma once

#include <unordered_map>

#include "Grid.hpp"
#include "Core.hpp"

class World;

class Block
{
public:
	Block ( World & world, sf::Vector2f gridIndex );

	void Move ( Directions direction );
	void Draw ( sf::RenderTarget & target ) const;
	void Update ();

	bool CheckCollision ( Directions ) const;
	
	/*std::unordered_map <Directions, bool> const & GetWallCollisionState () const { return wallCollisionState; }
	std::unordered_map <Directions, bool> const & GetBlockCollisionState () const { return blockCollisionState; }*/

private:
	std::unordered_map <Directions, float> GetEdgesInWorldSpace ();

	bool CheckBlockCollision ( Directions );
	void UpdateCollisionState ();

	World * world;
	Grid const * grid;
	sf::Vector2f gridIndex;
	sf::RectangleShape rect;

	std::unordered_map <Directions, bool> wallCollisionState
		{ {Directions::left, false }, {Directions::right, false }, {Directions::up, false }, {Directions::down, false } };
	
	std::unordered_map <Directions, bool> blockCollisionState
		{ {Directions::left, false }, { Directions::right, false }, { Directions::up, false }, { Directions::down, false } };

};