#include "Slime_states.h"
#include "components\cmp_slime_properties.h"
#include "components\cmp_physics.h"
#include "components\cmp_animation.h"
#include "Prefabs.h"
#include "GameState.h"
#include "Engine.h"


double totalTimeS = 2;
double attackDelayS = 2;


using namespace sf;
using namespace std;

void  Slime_IdleState::execute(Entity *owner, double dt) noexcept
{
	auto p = owner->get_components<PhysicsComponent>()[0];
	auto sm = owner->get_components<StateMachineComponent>()[0];



	if (length(owner->getPosition() - _player->getPosition()) < 900.f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];

		if (length(owner->getPosition() - _player->getPosition()) < 800.f)
		{
			totalTimeS += dt;

			if (totalTimeS >= attackDelayS)
			{
				totalTimeS -= attackDelayS;
				sm->changeState("Attack");
			}

		}
		else if (length(owner->getPosition() - _player->getPosition()) < 300.f)
		{
			sm->changeState("flee");
		}
	}

	p->dampen({ 0.7f , 1.0f });

	if (owner->get_components<SlimePropertiesComponent>()[0]->getHealth() <= 0)
	{
		owner->get_components<PhysicsComponent>()[0]->setVelocity(sf::Vector2f(0, 0));
		owner->get_components<AnimationComponent>()[0]->currentimage.x = 0;
		owner->get_components<StateMachineComponent>()[0]->changeState("dead");
	}
}

void  Slime_FleeState::execute(Entity *owner, double dt) noexcept
{
	auto sm = owner->get_components<StateMachineComponent>()[0];
	auto p = owner->get_components<PhysicsComponent>()[0];

	if (length(owner->getPosition() - _player->getPosition()) > 900.f)
	{
		sm->changeState("idle");
	}

	if (length(owner->getPosition() - _player->getPosition()) < 800.f)
	{
		totalTimeS += dt;
		if (totalTimeS >= attackDelayS)
		{
			totalTimeS -= attackDelayS;
			sm->changeState("Attack");
		}

	}

	if (owner->get_components<SlimePropertiesComponent>()[0]->getHealth() <= 0)
	{
		owner->get_components<PhysicsComponent>()[0]->setVelocity(sf::Vector2f(0, 0));
		owner->get_components<AnimationComponent>()[0]->currentimage.x = 0;
		owner->get_components<StateMachineComponent>()[0]->changeState("dead");
	}

	if (_player->getPosition().x > owner->getPosition().x)
	{
		owner->get_components<AnimationComponent>()[0]->faceRight = false;
		p->impulse({ -5.0f , 0.0f });
		p->dampen({ 0.7f , 1.0f });
	}

	//follow left
	if (_player->getPosition().x < owner->getPosition().x)
	{
		owner->get_components<AnimationComponent>()[0]->faceRight = true;
		p->impulse({ 5.0f , 0.0f });
		p->dampen({ 0.7f , 1.0f });

	}
}


void  Slime_AttackState::execute(Entity *owner, double dt) noexcept
{
	auto p = owner->get_components<PhysicsComponent>()[0];
	auto a = owner->get_components<AnimationComponent>()[0];
	auto sm = owner->get_components<StateMachineComponent>()[0];

	p->dampen({0.7f , 0.f});

	if (length(owner->getPosition() - _player->getPosition()) < 300.f)
	{
		sm->changeState("flee");
	}


	if (_player->getPosition().x > owner->getPosition().x)
	{
		a->faceRight = true;
	
	}

	//follow left
	if (_player->getPosition().x < owner->getPosition().x)
	{
		a->faceRight = false;
		
	}


	if (a->attackImgNo >= 5)
	{
		slimeBlast();
		a->attackImgNo = 0;
		owner->get_components<StateMachineComponent>()[0]->changeState("idle");
	}


	//if (length(owner->getPosition() - _player->getPosition()) < 200.f)
	//{
		//sm->changeState("flee");
	//}

	if (owner->get_components<SlimePropertiesComponent>()[0]->getHealth() <= 0)
	{
		owner->get_components<PhysicsComponent>()[0]->setVelocity(sf::Vector2f(0, 0));
		owner->get_components<AnimationComponent>()[0]->currentimage.x = 0;
		owner->get_components<StateMachineComponent>()[0]->changeState("dead");
	}

}


void  Slime_DeadState::execute(Entity *owner, double dt) noexcept
{
	auto me_anim = owner->get_components<AnimationComponent>()[0];
	if (me_anim->currentimage.x == 7)
	{


		_bufferDeath = *(Resources::get<SoundBuffer>("Slime_Sounds/Slime_Death.wav"));
		_soundDeath.setBuffer(_bufferDeath);

		_soundDeath.play();
		_soundDeath.setVolume(sfxVolume);

		me_anim->currentimage.x = 0;
		makeCoin(owner->getPosition());
		makeCoin(owner->getPosition());
		makeCoin(owner->getPosition());
		makeCoin(owner->getPosition());
		me_anim->pause = true;
		owner->setForDelete();
	}
}