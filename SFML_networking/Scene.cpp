#include "Scene.h"



Scene::Scene(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;
	par.setSize(sf::Vector2f(50,50));
}


Scene::~Scene()
{
}

void Scene::update(float dt, sf::Vector2f pos)
{

	par.setPosition(pos);
}

void Scene::handleInput()
{
}

void Scene::render()
{
	beginRender();

	window->draw(par);
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