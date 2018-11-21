#pragma once
#include <SFML\Graphics.hpp>
#include "Sprite.h"
class Sprite : public sf::RectangleShape
{
public:
	Sprite(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Sprite();

	virtual void update(float dt) = 0;
	void setVelocity(sf::Vector2f vel);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity();

	void setAcceleration(sf::Vector2f acc);
	void setAcceleration(float accX, float accY);
	sf::Vector2f getAcceleration();

	void setAlive(bool al);
	bool getAlive();

	void applyForce(sf::Vector2f force);
	void setForce(sf::Vector2f force);
	void setMass(float ma);
	
	float getMass();



protected:
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	bool alive;
	float mass;


};