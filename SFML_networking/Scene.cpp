#include "Scene.h"



Scene::Scene(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;
}


Scene::~Scene()
{
}

void Scene::update(float dt)
{
}

void Scene::handleInput()
{
}

void Scene::render()
{
	beginRender();


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