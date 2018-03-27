#pragma once
#pragma once

#include "cmp_physics.h"

class PlayerPhysicsComponent : public PhysicsComponent {
protected:
	b2Vec2 _size;
	sf::Vector2f _maxVelocity;
	bool _grounded;
	float _groundspeed;
	double switchtime;
	double totaltime;
	bool isGrounded() const;

public:

	void CollisionCheck(double dt);

	b2Body getBody();

	void update(double dt) override;

	explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size);

	PlayerPhysicsComponent() = delete;
};
