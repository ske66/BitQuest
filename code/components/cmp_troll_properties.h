#pragma once
#include <ecm.h>
#include "engine.h"

class TrollPropertiesComponent : public Component
{
protected:
	float _health = 10;
	float damageDelay = 0.5;
	float totalTime = 0;

public:
	sf::IntRect rect;
	bool immortal = true;
	float trollDamage = 3;
	std::vector<std::shared_ptr<Entity>> _trolls;
	std::shared_ptr<Entity> _player;
	explicit TrollPropertiesComponent(Entity* p);
	sf::IntRect checkHealth();
	TrollPropertiesComponent() = delete;
	double getHealth();
	void takeDamage(double);
	void update(double dt);
	void render() override;
	void checkContact(double dt);
};