
#include "cmp_player_bullet.h"
#include "engine.h"
#include "cmp_player_physics.h"
#include "cmp_player_controller.h"
#include <iostream>
#include <chrono>
#include <string>

PlayerBulletComponent::PlayerBulletComponent(Entity* p)
	: Component(p)
{
	_player = _parent->scene->ents.find("player")[0];
	auto d = _player->get_components<AnimationComponent>()[0];

	_bulletDamage = 1;
	_bulletSpeed = 10;

	if (d->faceRight == true)
	{
		facingRight = true;
	}
	else
	{
		facingRight = false;
	}
}

void PlayerBulletComponent::update(double dt)
{
	moveBullet(dt);
	checkContact(dt);
}

void PlayerBulletComponent::render()
{}

void PlayerBulletComponent::moveBullet(double dt)
{
	auto b = _parent->get_components<PhysicsComponent>()[0];
	auto d = _player->get_components<AnimationComponent>()[0];


	if (facingRight == false)
	{
		b->impulse(sf::Vector2f(-_bulletSpeed, 3));
		b->dampen({ 0.7f , 0.f });
	}
	else
	{
		b->impulse(sf::Vector2f(_bulletSpeed, 3));
		b->dampen({ 0.7f , 0.f });
	}

	if (length(_parent->getPosition() - _player->getPosition()) > 700)
	{
		_parent->setForDelete();
	}
}

void PlayerBulletComponent::checkContact(double dt)
{

	//only check when near player (saves performance evaluation of position Runs in Constant time loop runs in liniar time avoid where possible)
	

		auto b = _parent->get_components<PhysicsComponent>()[0];
		auto cs = _parent->get_components<PhysicsComponent>()[0]->getTouching();

		auto playerPhys = _player->get_components<PlayerPhysicsComponent>()[0];

		for (auto c : cs)
		{
			//if (c->GetFixtureA() == playerPhys->getFixture() || c->GetFixtureB() == playerPhys->getFixture())
			//{
				//_player->get_components<PlayerControlerComponent>()[0]->takeDamage(_bulletDamage, dt);
				//_parent->setForDelete();
			//}
		}
	
}

