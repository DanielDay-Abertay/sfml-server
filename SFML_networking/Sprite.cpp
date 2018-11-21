#include "Sprite.h"

Sprite::Sprite(const sf::Vector2f & size) : RectangleShape(size)
{
	alive = false;
}

Sprite::~Sprite()
{

}

void Sprite::setVelocity(sf::Vector2f vel)
{
	velocity = vel;
	
}

void Sprite::setVelocity(float velX, float velY)
{
	velocity.x = velX;
	velocity.y = velY;
}

sf::Vector2f Sprite::getVelocity()
{
	return velocity;
}

void Sprite::setAcceleration(sf::Vector2f acc)
{
	acceleration = acc;
}

void Sprite::setAcceleration(float accX, float accY)
{
	acceleration.x = accX;
	acceleration.y = accY;
}

sf::Vector2f Sprite::getAcceleration()
{
	return acceleration;
}

void Sprite::setAlive(bool al)
{
	alive = al;
}

bool Sprite::getAlive()
{
	return alive;
}

void Sprite::applyForce(sf::Vector2f force)
{
	sf::Vector2f temp;
	temp = force / mass;
	acceleration += temp;
}

void Sprite::setForce(sf::Vector2f force)
{}


void Sprite::setMass(float ma)
{
	mass = ma;
}

float Sprite::getMass()
{
	return mass;
}
