#include "troll_states.h"
#include "components\cmp_troll_properties.h"
#include "components\cmp_physics.h"
#include "components\cmp_animation.h"
#include "components\cmp_hurt.h"

double totalTimeT = 2;
double attackDelayT = 3;

void  Troll_IdleState::execute(Entity *owner, double dt) noexcept
{
	auto p = owner->get_components<PhysicsComponent>()[0];
	auto sm = owner->get_components<StateMachineComponent>()[0];

	if (length(owner->getPosition() - _player->getPosition()) < 500.f)
	{
		if (length(owner->getPosition() - _player->getPosition()) < 100.f)
		{
			sm->changeState("idle");
		}
		else
		{
			sm->changeState("chase");
		}
		
	}

}

void  Troll_ChaseState::execute(Entity *owner, double dt) noexcept
{
	auto sm = owner->get_components<StateMachineComponent>()[0];
	auto p = owner->get_components<PhysicsComponent>()[0];

	if (length(owner->getPosition() - _player->getPosition()) > 500.f)
	{
		sm->changeState("idle");
	}
	
	if(length(owner->getPosition() - _player->getPosition()) < 100.f)
	{
		sm->changeState("idle");
	}


	if (length(owner->getPosition() - _player->getPosition()) < 200.f)
	{
		totalTimeT += dt;
		if (totalTimeT >= attackDelayT)
		{
			totalTimeT -= attackDelayT;
			sm->changeState("Attack");
		}
		
	}





	if (_player->getPosition().x > owner->getPosition().x)
	{
		owner->get_components<AnimationComponent>()[0]->faceRight = true;
		p->impulse({ 2.0f , 0.0f });
		p->dampen({ 0.7f , 1.0f });
	}

	//follow left
	if (_player->getPosition().x < owner->getPosition().x)
	{
		owner->get_components<AnimationComponent>()[0]->faceRight = false;
		p->impulse({ -2.0f , 0.0f });
		p->dampen({ 0.7f , 1.0f });

	}
}


void  Troll_AttackState::execute(Entity *owner, double dt) noexcept
{
	auto p = owner->get_components<PhysicsComponent>()[0];
	auto a = owner->get_components<AnimationComponent>()[0];
	auto sm = owner->get_components<StateMachineComponent>()[0];

	
	if (a->attackImgNo >= 6)
	{
		a->attackImgNo = 0;
		sm->changeState("chase");
	}


	if (length(owner->getPosition() - _player->getPosition()) > 200.f)
	{
		sm->changeState("chase");
	}

	
}


void  Troll_DeadState::execute(Entity *owner, double dt) noexcept
{
	auto me_anim = owner->get_components<AnimationComponent>()[0];
	if (me_anim->currentimage.x == 7)
	{
		me_anim->currentimage.x = 0;
		me_anim->pause = true;
		owner->setForDelete();
	}
}