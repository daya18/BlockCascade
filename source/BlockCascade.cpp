#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window( sf::VideoMode { { 1280, 720 } }, {} );

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type )
			{
			case sf::Event::Closed:
				window.close ();
				return 0;
			}
		}
			
		window.clear ();
		window.display ();
	}
	return 0;
}
