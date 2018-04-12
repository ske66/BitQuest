#pragma once
#include <ecm.h>
#include "engine.h"

class GoblinPropertiesComponent : public Component
{
protected:
	float _health = 2;
	float damageDelay = 0.2;
	float totalTime = 0;
public:

	float goblinDamage = 1;
	bool immortal = true;
	std::shared_ptr<Entity> _player;
	explicit GoblinPropertiesComponent(Entity* p);
	void checkHealth();
	GoblinPropertiesComponent() = delete;
	double getHealth();
	void takeDamage(double);
	void update(double dt);
	void render() override;
	void checkContact(double dt);
};
