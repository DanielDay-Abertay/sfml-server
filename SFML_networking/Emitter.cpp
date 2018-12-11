#include "Emitter.h"



Emitter::Emitter()
{
}


Emitter::~Emitter()
{
}

void Emitter::init(int amount, sf::Vector2f pos, sf::Texture* texture, int seed)
{
	particleVec = new std::vector<Particle*>;
	
	position = pos;

	for (int i = 0; i < amount; i++)
	{
		particleVec->push_back(new Particle(seed));
		particleVec->back()->init(position);
		particleVec->back()->setTexture(texture);
	}

}

void Emitter::cleanUp()
{
	for (auto it : *particleVec)
	{
		delete it;
		it = nullptr;
	}
	delete particleVec;
	particleVec = nullptr;
}

void Emitter::update(float dt)
{
	for (auto par : *particleVec)
	{
		if (par->offScreen())
		{

			par->init(position);		
		}
		else
		{
			par->update(dt);
		}	
	}
}

void Emitter::render(sf::RenderWindow* window)
{
	for (auto par : *particleVec)
	{
		window->draw(*par);
	}
}

void Emitter::setLocation(sf::Vector2f pos)
{
	position = pos;
}
