#include "gavin_states.h"
#include "prefabs.h"
#include "components/cmp_sprite.h"
#include "components\cmp_player_physics.h"
#include "components/cmp_animation.h"
#include <iostream>
#include "Player_states.h"


using namespace sf;
using namespace std;


void  Player_IdleState::execute(Entity *owner, double dt) noexcept
{
	auto me = owner->get_components<StateMachineComponent>()[0]; 
	auto p = owner->get_components<PlayerPhysicsComponent>()[0];

	p->dampen({ 0.7f , 0 });
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		me->changeState("walk_left");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		me->changeState("walk_right");
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		me->changeState("Attack");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		me->changeState("jump");
	}

}

void  Player_MoveLeftState::execute(Entity *owner, double dt) noexcept
{
	auto p = owner->get_components<PlayerPhysicsComponent>()[0];
	
	if (!Keyboard::isKeyPressed(Keyboard::A))
	{
		owner->get_components<StateMachineComponent>()[0]->changeState("idle");
	}
	p->impulse({ -9.0f , 0.0f });
	p->dampen({ 1.7f , 1.0f });
	cout << "ml" << endl;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		owner->get_components<StateMachineComponent>()[0];
	}
}

void  Player_MoveRightState::execute(Entity *owner, double dt) noexcept
{

	if (!Keyboard::isKeyPressed(Keyboard::D))
	{
		owner->get_components<StateMachineComponent>()[0]->changeState("idle");
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		owner->get_components<StateMachineComponent>()[0];
	}

	auto p = owner->get_components<PlayerPhysicsComponent>()[0];
	
	p->impulse({ 9.0f , 0.0f });
	p->dampen({ 1.7f , 1.0f });
	
	cout << "mr" << endl;
}

void  Player_AttackState::execute(Entity *owner, double dt) noexcept
{

	auto me = owner->get_components<StateMachineComponent>()[0];

	auto p = owner->get_components<PlayerPhysicsComponent>()[0];

	p->setVelocity({ 0.f , 0.f });
	cout << "attack" << endl;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		me->changeState("walk_left");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		me->changeState("walk_right");
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		me->changeState("Attack");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		me->changeState("jump");
	}
}