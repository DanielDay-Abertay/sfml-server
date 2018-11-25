#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Input.h"
#include "Particle.h"
#include <list>
#include "Emitter.h"
#include "Server.h"
struct playerPos;

class Scene
{
public:
	Scene(sf::RenderWindow* hwnd, Input* in, Server* ser);
	~Scene();

	void update(float dt, std::vector<playerPos> *playerPosVec);
	void handleInput();
	void render();


private:
	void beginRender();
	void endRender();
	sf::RenderWindow* window;
	Input* input;
	Server* server;
	std::vector<Emitter> parVec;
};

