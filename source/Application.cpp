#include "Application.hpp"

#include <chrono>

Application::Application ()
:
	grid { 30, { 15, 15 }, 1 },
	window { sf::VideoMode { sf::Vector2u { grid.GetSize () } }, "BlockCascade", sf::Style::Titlebar | sf::Style::Close },
	world ( *this )
{
}

void Application::Run () 
{
	while (window.isOpen () && !exit )
	{
		Render ();
		Update ();
		HandleEvents ();
	}
}

void Application::HandleEvents ()
{
	sf::Event event;

	while (window.pollEvent ( event ))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close ();
			return;

		case sf::Event::Resized:
			window.setView ( sf::View { sf::FloatRect {
				{ 0.0f, 0.0f },
				{
					static_cast <float> (event.size.width),
					static_cast <float> (event.size.height)
				}
			} } );

			break;
		}

		world.HandleEvent ( event );
	}
}

void Application::Update ()
{
	static std::chrono::steady_clock::time_point lastUpdateTime { std::chrono::steady_clock::now () };

	auto updateDeltaMicroSeconds {
		std::chrono::duration_cast<std::chrono::microseconds> (
			std::chrono::steady_clock::now () - lastUpdateTime).count () };

	float updateDelta { static_cast <float> (updateDeltaMicroSeconds) / 1e+6f };

	world.Update ( updateDelta );

	lastUpdateTime = std::chrono::steady_clock::now ();
}

void Application::Render ()
{
	window.clear ();

	world.Draw ( window );

	window.display ();
}
