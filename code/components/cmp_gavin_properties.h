#pragma once
#include <ecm.h>
#include "engine.h"

class GavinPropertiesComponent : public Component
{
protected:
	float _health = 10;
	float damageDelay = 0.5;
	float totalTime = 0;

public:

	bool immortal = true;
	std::shared_ptr<Entity> _player;
	explicit GavinPropertiesComponent(Entity* p);
	void checkHealth();
	GavinPropertiesComponent() = delete;
	double getHealth();
	void takeDamage(double);
	void update(double dt);
	void render() override;
	void checkContact();
};