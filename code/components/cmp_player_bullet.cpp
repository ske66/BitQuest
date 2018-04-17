#include "cmp_orc_properties.h"
#include "cmp_player_bullet.h"
#include "engine.h"
#include "cmp_player_physics.h"
#include "cmp_player_controller.h"
#include "cmp_troll_properties.h"
#include "cmp_slime_properties.h"
#include "../SaveLoad.h"
#include <iostream>
#include <chrono>
#include <string>

PlayerBulletComponent::PlayerBulletComponent(Entity* p)
	: Component(p)
{
	_bulletDamage = SaveLoad::playerDamage;
	_trolls = _parent->scene->ents.find("troll");
	_slimes = _parent->scene->ents.find("slime");
	_orcs = _parent->scene->ents.find("orc");
	_player = _parent->scene->ents.find("player")[0];
	auto d = _player->get_components<AnimationComponent>()[0];
	auto b = _parent->get_components<PhysicsComponent>()[0];

	_bulletDamage = 1;
	_bulletSpeed = 20;
	_bulletArc = -10;
	_bulletDip = -5;

	if (d->faceRight == true)
	{
		facingRight = true;
	}
	else
	{
		facingRight = false;
	}

	if (facingRight == false)
	{
		b->getFixture()->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(-40.f,12.f),true);
	
	}
	else
	{
		b->getFixture()->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(40.f, 12.f), true);
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

	if (length(_parent->getPosition() - _player->getPosition()) > 1000)
	{
		_parent->setForDelete();
	}

}


void PlayerBulletComponent::checkContact(double dt)
{
	//auto orcs = _parent->scene->ents.find("orc");
	auto b = _parent->get_components<PhysicsComponent>()[0];
	auto cs = _parent->get_components<PhysicsComponent>()[0]->getTouching();


	for (auto c : cs)
	{
		for (auto o : _orcs)
		{
			if (c->GetFixtureB() == o->get_components<PhysicsComponent>()[0]->getFixture() || c->GetFixtureA() == o->get_components<PhysicsComponent>()[0]->getFixture())
			{
				o->get_components<OrcPropertiesComponent>()[0]->takeDamage(_bulletDamage);
				_parent->setForDelete();
			}

		}
		for (auto t : _trolls)
		{
			if (c->GetFixtureB() == t->get_components<PhysicsComponent>()[0]->getFixture() || c->GetFixtureA() == t->get_components<PhysicsComponent>()[0]->getFixture())
			{
				t->get_components<TrollPropertiesComponent>()[0]->takeDamage(_bulletDamage);
				_parent->setForDelete();
			}
		}
		for (auto s : _slimes)
		{
			if (c->GetFixtureB() == s->get_components<PhysicsComponent>()[0]->getFixture() || c->GetFixtureA() == s->get_components<PhysicsComponent>()[0]->getFixture())
			{
				s->get_components<SlimePropertiesComponent>()[0]->takeDamage(_bulletDamage);
				_parent->setForDelete();
			}
		}

	}
}