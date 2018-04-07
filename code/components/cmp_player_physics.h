#pragma once


#include "cmp_state_machine.h"
#include "cmp_physics.h"
#include "cmp_player_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>
#include "levelsystem.h"
#include "ecm.h"
#include "engine.h"
#include "cmp_gavin_physics.h"

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

	void MoveRight(double dt);
	void MoveLeft(double dt);

	b2Body getBody();

	void update(double dt) override;

	explicit PlayerPhysicsComponent(Entity* p, const sf::Vector2f& size);

	PlayerPhysicsComponent() = delete;
};
