#pragma once
#include <ecm.h>
#include "engine.h"

class GhostPropertiesComponent : public Component
{
protected:
	float _health = 2;
	float damageDelay = 2;
	float totalTime = 2;

public:

	sf::IntRect rect = sf::IntRect(0, 0, 100, 5);
	bool immortal = true;
	std::shared_ptr<Entity> _player;
	explicit GhostPropertiesComponent(Entity* p);
	void checkHealth();
	GhostPropertiesComponent() = delete;
	double getHealth();
	void takeDamage(double);
	void update(double dt);
	void render() override;
	void checkContact();
};