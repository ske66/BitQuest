#pragma once
#include <ecm.h>
#include "engine.h"

class GoblinPropertiesComponent : public Component
{
protected:
	float _health = 3;
	float damageDelay = 0.2;
	float totalTime = 0;
public:

	sf::IntRect rect = sf::IntRect(0,0,100,5);
	float goblinDamage = 1;
	bool immortal = true;
	std::shared_ptr<Entity> _player;
	explicit GoblinPropertiesComponent(Entity* p);
	sf::IntRect checkHealth();
	GoblinPropertiesComponent() = delete;
	double getHealth();
	void takeDamage(double);
	void update(double dt);
	void render() override;
	void checkContact(double dt);
};
