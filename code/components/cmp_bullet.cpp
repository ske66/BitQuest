#include "cmp_bullet.h"
#include "engine.h"
#include "cmp_player_physics.h"
#include "cmp_player_controller.h"
#include <iostream>
#include <chrono>
#include <string>

BulletComponent::BulletComponent(Entity* p)
	: Component(p)
{
	
	_player = _parent->scene->ents.find("player")[0];
	_gavin = _parent->scene->ents.find("gavin")[0];
	auto d = _gavin->get_components<AnimationComponent>()[0];

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

void BulletComponent::update(double dt)
{
	moveBullet(dt);
	checkContact(dt);
}

void BulletComponent::render()
{}

void BulletComponent::moveBullet(double dt)
{
	auto b = _parent->get_components<PhysicsComponent>()[0];
	auto d = _gavin->get_components<AnimationComponent>()[0];


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

	if(length(_parent->getPosition() - _gavin->getPosition()) > 700)
	{
		_parent->setForDelete();
	}
}

void BulletComponent::checkContact(double dt)
{
	
	//only check when near player (saves performance evaluation of position Runs in Constant time loop runs in liniar time avoid where possible)
	if (sf::length(_parent->getPosition() - _player->getPosition()) < 100.f)
	{

		auto b = _parent->get_components<PhysicsComponent>()[0];
		auto cs = _parent->get_components<PhysicsComponent>()[0]->getTouching();

		auto playerPhys = _player->get_components<PlayerPhysicsComponent>()[0];

		for (auto c : cs)
		{
			if (c->GetFixtureA() == playerPhys->getFixture() || c->GetFixtureB() == playerPhys->getFixture())
			{
				_player->get_components<PlayerControlerComponent>()[0]->takeDamage(_bulletDamage, dt);
				_parent->setForDelete();
			}
		}
	}
}

