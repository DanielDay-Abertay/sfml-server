#pragma once
#include "Particle.h"
#include <vector>

class Emitter
{
public:
	Emitter();
	~Emitter();

	void init(int amount, sf::Vector2f pos, sf::Texture* texture, int seed);
	void cleanUp();
	void update(float dt);
	void render(sf::RenderWindow* window);

	void setLocation(sf::Vector2f pos);
	sf::Vector2f getLocation() { return position; };

private:

	std::vector<Particle*>* particleVec;
	sf::Texture texture;

	sf::Vector2f position;
	sf::Vector2f direction;

	float speed;

};

