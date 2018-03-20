#pragma once

#include <ecm.h>
#include "cmp_actor_movement.h"

class EnemyAIComponent : public ActorMovementComponent 
{
protected:
	float _speed = 100.f;
public:
	explicit EnemyAIComponent(Entity* p);
	EnemyAIComponent() = delete;
	void render() override {}
	void update(double dt) override;
};