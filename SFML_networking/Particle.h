#pragma once
#include "SFML\Graphics.hpp"
#include "Sprite.h"
#include <iostream>
class Particle : public Sprite
{
public:
	Particle(int seed, const sf::Vector2f& size =sf::Vector2f(0.0f,0.0f));
	~Particle();
	void update(float dt);
	void setDirection(sf::Vector2f dir) { direction = dir; }

	void init(sf::Vector2f pos);
	bool offScreen();
	void reset();


	float speed;
	sf::Vector2f direction;
};

