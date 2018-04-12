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

	bool immortal = true;
	float trollDamage = 3;
	std::shared_ptr<Entity> _player;
	explicit TrollPropertiesComponent(Entity* p);
	void checkHealth();
	TrollPropertiesComponent() = delete;
	double getHealth();
	void takeDamage(double);
	void update(double dt);
	void render() override;
	void checkContact(double dt);
};