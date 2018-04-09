#include "gavin_states.h"
#include "prefabs.h"
#include <random>
#include <chrono>
#include "components/cmp_sprite.h"
#include "components/cmp_gavin_physics.h"
#include "components/cmp_animation.h"
#include <iostream>


using namespace sf;
using namespace std;

float _timer = 1.0f;
// Gavin ----------------------------------------------------------------------

void  Gavin_IdleState::execute(Entity *owner, double dt) noexcept
{
	// Don't move
	owner->get_components<GavinPhysicsComponent>()[0]->setVelocity(Vector2f(0, 0));

	
	 //Chase player when in range
	if(length(owner->getPosition() - _player->getPosition()) < 400.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("chase");
	}
}

void  Gavin_PrepAttackState::execute(Entity *owner, double dt) noexcept
{
	_timer -= dt;

	if (_timer <= 0)
	{
		owner->get_components<StateMachineComponent>()[0]->changeState("Attack");
		
	}
}



void  Gavin_ChaseState::execute(Entity *owner, double dt) noexcept
{
	//out of range
	if (!(length(owner->getPosition() - _player->getPosition()) < 400.0f))
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("idle");
	}

	auto g = owner->get_components<GavinPhysicsComponent>()[0];

	//follow right

	if (_player->getPosition().x > owner->getPosition().x)
	{
		owner->get_components<AnimationComponent>()[0]->faceRight = true;
		g->impulse({ 4.0f , 0.0f });
		g->dampen({ 0.7f , 1.0f });
	}

	//follow left
	if (_player->getPosition().x < owner->getPosition().x)
	{
		owner->get_components<AnimationComponent>()[0]->faceRight = false;
		g->impulse({ -4.0f , 0.0f });
		g->dampen({ 0.7f , 1.0f });
		
	}

	//in attack range
	if (length(owner->getPosition() - _player->getPosition()) < 150.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("prepAttack");
	}
	
}

void  Gavin_AttackState::execute(Entity *owner, double dt) noexcept
{
	//out of attack range
	if(!(length(owner->getPosition() - _player->getPosition()) < 150.0f))
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("idle");
	}

}