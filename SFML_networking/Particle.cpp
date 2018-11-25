#include "Particle.h"



Particle::Particle(int seed, const sf::Vector2f& size) : Sprite(seed, size)
{
	srand(seed);
}


Particle::~Particle()
{
}

void Particle::init(sf::Vector2f pos)
{

	
	float randX = rand() % 200;
	if (randX < 100)
	{
		randX *= -1;
	}
	else
	{
		randX -= 100;
	}
	float randY = rand() % 1000;
	if (randY < 500)
	{
		randY *= -1;
	}
	else
	{
		randY -= 500;
	}
	setVelocity(randX, randY);


	setSize(sf::Vector2f(50, 50));
	
	
	setAcceleration(0, 0);
	setAlive(true);
	speed = 100;
	setMass(1);

	setPosition(pos);
//	setFillColor(sf::Color(1, 0, 0));
}

void Particle::update(float dt)
{
	sf::Vector2f temp{ 0, 500 };
	applyForce(temp);

	sf::Vector2f velocityTemp = getVelocity();
	sf::Vector2f accelerationTemp = getAcceleration();
	//use temp variables to calculate new velocity
	velocityTemp += accelerationTemp * dt;
	setVelocity(velocityTemp);


	
	move(getVelocity() * dt);
	acceleration *= 0.f;
//	std::cout << "X: " << getPosition().x << " Y: " << getPosition().y << std::endl;

}

bool Particle::offScreen()
{
	if (getPosition().y > 1080)
	{
		return true;
	}
	else if (getPosition().x < 0)
	{
		return true;
	}
	else if (getPosition().x > 1920)
	{
		return true;
	}

	return false;
}

void Particle::reset()
{



}
