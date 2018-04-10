#pragma once
#include <ecm.h>
#include "engine.h"

class GavinPropertiesComponent : public Component
{
protected:
	float _health = 10;
	float damageDelay = 10;
	float totalTime;

public:

	explicit GavinPropertiesComponent(Entity* p);
	sf::IntRect checkHealth();
	GavinPropertiesComponent() = delete;
	double getHealth();
	void takeDamage(double);
	void update(double dt);
	void render() override;

};