#include "cmp_player_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>
#include "levelsystem.h"
#include "ecm.h"
#include "engine.h"
#include "cmp_player_status.h"
#include "cmp_gavin_physics.h"

using namespace std;
using namespace sf;
using namespace Physics;

bool PlayerPhysicsComponent::isGrounded() const {
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


void PlayerPhysicsComponent::update(double dt) {

	const auto pos = _parent->getPosition();
	
	if (pos.y > ls::getHeight() * ls::getTileSize())
	{
		teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	}
	

	if (getVelocity().x == 0 && isGrounded() == true && _parent->getState() != "attack")
	{
		_parent->setState("idle"); 
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		_parent->setState("attack");
	}

	if (Keyboard::isKeyPressed(Keyboard::Left) ||
		Keyboard::isKeyPressed(Keyboard::Right)) 
	{
		// Moving Either Left or Right
		if (Keyboard::isKeyPressed(Keyboard::Right)) 
		{
			_parent->setState("walk_right");
			if (getVelocity().x < _maxVelocity.x)
				impulse({ (float)(dt * _groundspeed), 0 });
			
		}
		else 
		{
			_parent->setState("walk_left");
			if (getVelocity().x > -_maxVelocity.x)
				impulse({ -(float)(dt * _groundspeed), 0 });

		}
	}
	else 
	{
		// Dampen X axis movement
		dampen({ 0.7f, 1.0f });
	}

	// Handle Jump
	if (Keyboard::isKeyPressed(Keyboard::Up)) 
	{
		_grounded = isGrounded();
		if (_grounded) {
			_parent->setState("jump");
			setVelocity(Vector2f(getVelocity().x,  300.f));
			teleport(Vector2f(pos.x, pos.y - 5.0f));
			impulse(Vector2f(0, -100.f));

		}
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


	CollisionCheck(dt);
	PhysicsComponent::update(dt);
}



void PlayerPhysicsComponent::CollisionCheck(double dt)
{
	auto g = _parent->scene->ents.find("gavin")[0];
	auto cs = getTouching();


	for (auto c : cs)
	{
		if (c->GetFixtureA() == g->get_components<GavinPhysicsComponent>()[0]->getFixture())
		{
			

			if (g->getState() == "attack")
			{
				totaltime -= switchtime;
				_parent->get_components<PlayerStatusComponent>()[0]->takeDamage(1.0);
				std::cout << _parent->get_components<PlayerStatusComponent>()[0]->getHealth() << std::endl;
			}

		}

	}

}


PlayerPhysicsComponent::PlayerPhysicsComponent(Entity* p,
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
	teleport(ls::getTilePosition(ls::findTiles(ls::START)[0]));

}

