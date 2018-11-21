#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Input.h"
#include "Particle.h"
class Scene
{
public:
	Scene(sf::RenderWindow* hwnd, Input* in);
	~Scene();

	void update(float dt, sf::Vector2f pos);
	void handleInput();
	void render();


private:
	void beginRender();
	void endRender();
	sf::RenderWindow* window;
	Input* input;

	Particle par;
};

