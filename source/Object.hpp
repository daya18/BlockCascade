#pragma once

#include "Core.hpp"
#include "Block.hpp"

using ObjectConfiguration = std::vector <sf::Vector2f>;

class World;

class Object
{
public:
	Object () {}

	Object ( 
		World & world, 
		std::vector <ObjectConfiguration> const & orientationConfigurations, 
		sf::Vector2f const & gridIndex );
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
	void Rotate ();

private:
	void SetOrientation ( unsigned int configurationIndex );
	
	World * world;
	std::vector <ObjectConfiguration> const * orientationConfigurations;

	bool stable { false };
	sf::Vector2f gridIndex { 0u, 0u };
	std::vector <Block> blocks;
	unsigned int currentOrientation;
};