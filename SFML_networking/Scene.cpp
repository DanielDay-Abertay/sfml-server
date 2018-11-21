#include "Scene.h"
#include "Server.h"


Scene::Scene(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;
	par.setSize(sf::Vector2f(50,50));
}


Scene::~Scene()
{
}

void Scene::update(float dt, std::vector<playerPos> *playerPosVec)
{
	if (playerPosVec->size() != parVec.size())
	{
		parVec.push_back(par);
	}
	for (int i = 0; i < playerPosVec->size(); i++)
	{
		float x = playerPosVec->at(i).xPos;
		float y = playerPosVec->at(i).yPos;
		parVec[i].setPosition(sf::Vector2f(x, y));
	}
	

	//par.setPosition(pos);
}

void Scene::handleInput()
{
}

void Scene::render()
{
	beginRender();
	for (auto it : parVec)
	{
		window->draw(it);
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