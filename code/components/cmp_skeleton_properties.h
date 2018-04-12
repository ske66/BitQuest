#pragma once
#include <ecm.h>
#include "engine.h"

class SkeletonPropertiesComponent : public Component
{
protected:
	float _health = 2;
	float damageDelay = 0.5;
	float totalTime = 0;

public:

	bool immortal = true;
	float skeletonDamage = 1;
	std::shared_ptr<Entity> _player;
	explicit SkeletonPropertiesComponent(Entity* p);
	void checkHealth();
	SkeletonPropertiesComponent() = delete;
	double getHealth();
	void takeDamage(double);
	void update(double dt);
	void render() override;
	void checkContact(double dt);
};