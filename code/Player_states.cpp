#include "gavin_states.h"
#include "prefabs.h"
#include "components/cmp_sprite.h"
#include "components\cmp_player_physics.h"
#include "components/cmp_animation.h"
#include <iostream>
#include "Player_states.h"
#include "components\cmp_player_controller.h"
#include "components\cmp_hurt.h"
#include "GameState.h"

using namespace sf;
using namespace std;


void  Player_IdleState::execute(Entity *owner, double dt) noexcept
{
	auto me = owner->get_components<StateMachineComponent>()[0]; 
	auto p = owner->get_components<PlayerPhysicsComponent>()[0];

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		owner->get_components<StateMachineComponent>()[0]->changeState("Attack");
	}

	//dampen if not jumping
	if (p->isGrounded() == true)
	{
		p->dampen({ 0.7f , 0 });
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		me->changeState("walk_left");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		me->changeState("walk_right");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		me->changeState("Attack");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		me->changeState("jump");
	}

	if (owner->get_components<PlayerControlerComponent>()[0]->getHealth() < 0)
	{
		owner->get_components<StateMachineComponent>()[0]->changeState("dead");
	}
}

void  Player_MoveLeftState::execute(Entity *owner, double dt) noexcept
{

	owner->get_components<AnimationComponent>()[0]->faceRight = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		owner->get_components<StateMachineComponent>()[0]->changeState("Attack");
	}

	auto p = owner->get_components<PlayerPhysicsComponent>()[0];
	

	if (!Keyboard::isKeyPressed(Keyboard::A))
	{
		owner->get_components<StateMachineComponent>()[0]->changeState("idle");
	}
	p->impulse({ -9.0f , 0.0f });
	p->dampen({ 1.7f , 1.0f });
	
	if (owner->get_components<PlayerControlerComponent>()[0]->getHealth() == 0)
	{
		owner->get_components<StateMachineComponent>()[0]->changeState("dead");
	}
}

void  Player_MoveRightState::execute(Entity *owner, double dt) noexcept
{
	owner->get_components<AnimationComponent>()[0]->faceRight = true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		owner->get_components<StateMachineComponent>()[0]->changeState("Attack");
	}

	if (!Keyboard::isKeyPressed(Keyboard::D))
	{
		owner->get_components<StateMachineComponent>()[0]->changeState("idle");
	}

	auto p = owner->get_components<PlayerPhysicsComponent>()[0];
	
	p->impulse({ 9.0f , 0.0f });
	p->dampen({ 1.7f , 1.0f });
	
	if (owner->get_components<PlayerControlerComponent>()[0]->getHealth() == 0)
	{
		owner->get_components<StateMachineComponent>()[0]->changeState("dead");
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		owner->get_components<StateMachineComponent>()[0]->changeState("Attack");
	}

}

void  Player_AttackState::execute(Entity *owner, double dt) noexcept
{

	auto me = owner->get_components<StateMachineComponent>()[0];
	auto me_anim = owner->get_components<AnimationComponent>()[0];
	auto p = owner->get_components<PlayerPhysicsComponent>()[0];

	//reset attack animation when done
	if (me_anim->attackImgNo >= 6)
	{
		me_anim->attackImgNo = 0;
		me->changeState("idle");
	}

	//lock movement when attacking
	if (me_anim->attackImgNo == 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			owner->get_components<StateMachineComponent>()[0]->changeState("Attack");
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			me->changeState("walk_left");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			me->changeState("walk_right");
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			me->changeState("jump");
		}
	}
	if (owner->get_components<PlayerControlerComponent>()[0]->getHealth() < 0)
	{
		me->changeState("dead");
	}
}

void  Player_DeadState::execute(Entity *owner, double dt) noexcept
{

	auto me_anim = owner->get_components<AnimationComponent>()[0];

	if (me_anim->currentimage.x >= 5)
	{
		me_anim->pause = true;
		
	}
	

}