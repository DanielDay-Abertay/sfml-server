#include "Scene.h"
#include "Server.h"


Scene::Scene(sf::RenderWindow* hwnd, Input* in, Server* ser)
{
	window = hwnd;
	input = in;
	server = ser;
}

Scene::~Scene()
{
}

void Scene::update(float dt, std::vector<playerPos> *playerPosVec)
{
	if (playerPosVec->size() != parVec.size())
	{
		Emitter em;

		float x = playerPosVec->back().xPos;
		float y = playerPosVec->back().yPos;
		sf::Vector2f pos{ x, y };
		em.init(10, pos, nullptr, server->getSeed());
		parVec.push_back(em);
		return;
	}
	for (int i = 0; i < playerPosVec->size(); i++)
	{

		float x = playerPosVec->at(i).xPos;
		float y = playerPosVec->at(i).yPos;
		parVec[i].setLocation(sf::Vector2f(x, y));
		parVec[i].update(dt);
	}
}

void Scene::handleInput()
{
}

void Scene::render()
{
	beginRender();
	for (auto it : parVec)
	{
		it.render(window);
	}
	endRender();
}

void Scene::beginRender()
{
	window->clear(sf::Color::Black);
}

void Scene::endRender()
{
	window->display();
}

