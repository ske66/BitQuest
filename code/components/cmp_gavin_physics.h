#pragma once
#pragma once
#pragma once

#include "cmp_physics.h"

class GavinPhysicsComponent : public PhysicsComponent {
protected:
	b2Vec2 _size;
	sf::Vector2f _maxVelocity;
	bool _grounded;
	float _groundspeed;

	bool isGrounded() const;

	int i;

public:

	b2Body getBody();

	void update(double dt) override;

	explicit GavinPhysicsComponent(Entity* p, const sf::Vector2f& size);

	GavinPhysicsComponent() = delete;

	
};
