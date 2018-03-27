#include "cmp_player_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>
#include "levelsystem.h"
#include "ecm.h"
#include "engine.h"
#include "cmp_gavin_physics.h"

using namespace std;
using namespace sf;
using namespace Physics;

bool GavinPhysicsComponent::isGrounded() const {
	auto touch = getTouching();
	const auto& pos = _body->GetPosition();
	const float halfPlrHeigt = _size.y * .5f;
	const float halfPlrWidth = _size.x * .52f;
	b2WorldManifold manifold;
	for (const auto& contact : touch) {
		contact->GetWorldManifold(&manifold);
		const int numPoints = contact->GetManifold()->pointCount;
		bool onTop = numPoints > 0;
		// If all contacts are below the player.
		for (int j = 0; j < numPoints; j++) {
			onTop &= (manifold.points[j].y < pos.y - halfPlrHeigt);
		}
		if (onTop) {
			return true;
		}
	}

	return false;
}


void GavinPhysicsComponent::update(double dt) {

	const auto pos = _parent->getPosition();

	if (pos.y > ls::getHeight() * ls::getTileSize())
	{
		//		teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	}

	{
		// Dampen X axis movement
		dampen({ 0.7f, 1.0f });
	}


	//Are we in air?
	if (!_grounded)
	{
		// Check to see if we have landed yet
		_grounded = isGrounded();
		// disable friction while jumping
		setFriction(0.f);
	}
	else
	{
		setFriction(0.1f);
	}

	// Clamp velocity.
	auto v = getVelocity();
	v.x = copysign(min(abs(v.x), _maxVelocity.x), v.x);
	v.y = copysign(min(abs(v.y), _maxVelocity.y), v.y);
	setVelocity(v);




	PhysicsComponent::update(dt);
}

GavinPhysicsComponent::GavinPhysicsComponent(Entity* p,
	const Vector2f& size)
	: PhysicsComponent(p, true, size) {
	_size = sv2_to_bv2(size, true);
	_maxVelocity = Vector2f(400.f, 800.f);
	//	_fixture->SetDensity(0.2);
	_groundspeed = 200.f;
	_grounded = false;
	_body->SetSleepingAllowed(false);
	_body->SetFixedRotation(true);
	//Bullet items have higher-res collision detection
	_body->SetBullet(true);
}