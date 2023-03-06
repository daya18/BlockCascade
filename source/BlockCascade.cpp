#include <iostream>
#include <array>
#include <chrono>
#include <limits>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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
			cellSize * cellCount.x + ( gutterSize * ( cellCount.x - 1 ) ),
			cellSize * cellCount.y + ( gutterSize * ( cellCount.y - 1 ) ),
		}; 
	};


	sf::Vector2u const & IndexToPosition ( sf::Vector2u index ) const {
		return {
			index.x * cellSize + gutterSize * index.x,
			index.y * cellSize + gutterSize * index.y
		};
	}
	
	sf::Vector2u const & PositionToIndex () const; // To be defined
	
	unsigned int GetCellSize () const { return cellSize; }
	sf::Vector2u const & GetCellCount () const { return cellCount; };

private:
	unsigned int cellSize;
	sf::Vector2u cellCount;
	unsigned int gutterSize;

};

enum Directions { left, right, up, down };

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
		else if (rect.getPosition ().y + rect.getSize().y >= grid.GetSize ().y)
			return { true, Directions::down };

		return { false };
	}

private:
	Grid const & grid;
	sf::Vector2u gridIndex;
	sf::RectangleShape rect;
};

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
				if (wallCollisionDirection == direction )
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
		if ( ! stable )
		{
			if ( ( nextDropIn -= delta ) < 0.0f)
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

class ObjectGenerator
{
public:
	Object Generate ( Grid const & grid ) const
	{
		return { grid, objectTypeDefinitions[0] };
	}

private:

	std::vector <std::vector <ObjectConfiguration>> objectTypeDefinitions
	{
		// Square
		{
			{ { 0u, 0u }, { 1u, 0u }, { 1u, 1u }, { 0u, 1u } }
		},

		// Line
		{
			{ { 0u, 0u }, { 1u, 0u }, { 2u, 0u } },
			{ { 0u, 0u }, { 0u, 1u }, { 0u, 2u } }
		},

		// L
		{
			{ { 0u, 0u }, { 0u, 1u }, { 1u, 1u }, { 2u, 1u } }
		}
	};
};

int main ()
{
	Grid grid { 30, { 15, 20 }, 1 };

	sf::RenderWindow window { sf::VideoMode{ grid.GetSize () }, "BlockCascade", sf::Style::Titlebar | sf::Style::Close};

	ObjectGenerator objectGenerator;
	Object object = objectGenerator.Generate ( grid );

	std::chrono::steady_clock::time_point lastUpdateTime { std::chrono::steady_clock::now () };

	while (window.isOpen ())
	{
		sf::Event event;
		while (window.pollEvent ( event ))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close ();
				return 0;

			case sf::Event::Resized:
				window.setView ( sf::View { sf::FloatRect {
					{ 0.0f, 0.0f },
					{
						static_cast <float> (event.size.width),
						static_cast <float> (event.size.height)
					}
				} } );

				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Right: object.Move ( Directions::right ); break;
				case sf::Keyboard::Left: object.Move ( Directions::left ); break;
				}
				break;
			}
		}

		window.clear ();

		object.Draw ( window );

		window.display ();

		auto updateDeltaMicroSeconds {
			std::chrono::duration_cast<std::chrono::microseconds> (
				std::chrono::steady_clock::now () - lastUpdateTime).count () };
		
		float updateDelta { static_cast <float> (updateDeltaMicroSeconds) / 1e+6f };

		object.Update ( updateDelta );

		lastUpdateTime = std::chrono::steady_clock::now ();
	}
	return 0;
}
