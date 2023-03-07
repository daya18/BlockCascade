#pragma once

#include "Core.hpp"
#include "Block.hpp"

using ObjectConfiguration = std::vector <sf::Vector2u>;

class World;

class Object
{
public:
	Object () {}

	Object ( 
		World & world, 
		std::vector <ObjectConfiguration> const & orientationConfigurations, 
		sf::Vector2u const & gridIndex );
	/*
	Object ( Object const & ) = delete;
	Object ( Object && ) {};
	
	Object & operator = ( Object const & ) = delete;
	Object & operator = ( Object && ) = default;*/

	void Move ( Directions direction );
	void Draw ( sf::RenderTarget & target );
	void Update ( float delta );
	bool CheckCollision ( Directions ) const;

	std::vector <Block> & GetBlocks () { return blocks; }
	bool CheckStable () const { return stable; }

private:
	/*void SetOrientation ( unsigned int orientation )
	{

	}*/

	using Configuration = char[3][3];

	bool stable { false };
	sf::Vector2u gridIndex { 0u, 0u };
	std::vector <Block> blocks;
};