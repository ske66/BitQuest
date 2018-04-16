
#include "cmp_Slime_bullet.h"
#include "engine.h"
#include "cmp_player_physics.h"
#include "cmp_player_controller.h"
#include <iostream>
#include "system_physics.h"
#include <limits>
#include <math.h>

SlimeBulletComponent::SlimeBulletComponent(Entity* p)
	: Component(p)
{
	_player = _parent->scene->ents.find("player")[0];
	auto d = _parent->scene->ents.find("slime")[0]->get_components<AnimationComponent>()[0];
	//b->getFixture()->GetBody().

	_bulletDamage = 1;
	_bulletSpeed = 20;
	_bulletArc = -10;
	_bulletDip = -5;

	/*
	double distance = (playerp->getFixture()->GetBody()->GetPosition().x - b->getFixture()->GetBody()->GetPosition().x);

	
	double angle;

	if (s->faceRight == false)
	{
		angle = 340;
	}
	else
	{
		angle = 60;
	}

	Over = distance * 40; //9.8 is constant for gravity
	//------------------------------------------------------------
	TempUnder = (2 * cos(angle * 3.14159265359 / 180));
	TempUnder2 = sin(angle * 3.14159265359 / 180);
	Under = TempUnder * TempUnder2;
	SumOf = Over / Under;
	V = sqrt(SumOf);
	Vx = V * cos(angle * 3.14159 / 180);
	Viy = V * sin(angle * 3.14159 / 180);

	Velocity_vector = b2Vec2(Vx, Viy);
	*/
	if (d->faceRight == true)
	{
		facingRight = true;
	}
	else
	{
		facingRight = false;
	}


}
void SlimeBulletComponent::update(double dt)
{
	checkContact(dt);
	moveBullet(dt);
	
}

void SlimeBulletComponent::render()
{}

void SlimeBulletComponent::moveBullet(double dt)
{
	auto b = _parent->get_components<PhysicsComponent>()[0];

	if (facingRight == false)
	{
		b->impulse({ -8.f , 0.f });
		b->dampen({ 0.7f , 1.f });
		
	}
	else
	{
		b->impulse({ 8.f , 0.f });
		b->dampen({ 0.7f , 1.f });
	}
}


void SlimeBulletComponent::checkContact(double dt)
{
	auto b = _parent->get_components<PhysicsComponent>()[0];
	auto cs = _parent->get_components<PhysicsComponent>()[0]->getTouching();
	auto p = _player->get_components<PlayerPhysicsComponent>()[0];

	for (auto c : cs)
	{
		if (c->GetFixtureA() == p->getFixture() || c->GetFixtureB() == p->getFixture())
		{
			_player->get_components<PlayerControlerComponent>()[0]->takeDamage(_bulletDamage,dt);
			_parent->setForDelete();
		}
		//else if()

	}

}
