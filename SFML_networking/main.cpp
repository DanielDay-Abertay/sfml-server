#include <SFML\OpenGL.hpp>
#include <SFML\Network.hpp>
#include "Scene.h"
#include <iostream>
#include "Server.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");


	Input input;

	sf::Clock clock;
	sf::Clock newclock;
	float deltaTime;
	bool close = false;
	Server server;

	

	server.udpBind();
	

	
	Scene scene(&window, &input);
//	scene.init();


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				close = true;
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0, 0,
					event.size.width, event.size.height)));
				break;
			case sf::Event::MouseMoved:
				input.setMousePos(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::KeyPressed:
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::MouseButtonPressed:
				input.setMouseDown(event.mouseButton.button);
				break;
			case sf::Event::MouseButtonReleased:
				input.setMouseUp(event.mouseButton.button);
				break;
			default:
				// don't handle other events
				break;
			}
		}
		if (!close) {
			deltaTime = clock.restart().asSeconds();

			server.listener();
			
			scene.update(deltaTime, &server.getPos());
			scene.render();
			//server.confirmTimeStamp();
		}
		


	}
}