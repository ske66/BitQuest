#include "goblin_states.h"
#include "components\cmp_physics.h"
#include "components\cmp_animation.h"

void  Goblin_IdleState::execute(Entity *owner, double dt) noexcept
{
	// Don't move
	owner->get_components<PhysicsComponent>()[0]->setVelocity(sf::Vector2f(0, 0));

	//Chase player when in range
	if (length(owner->getPosition() - _player->getPosition()) < 300.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("chase");
	}
}

void  Goblin_ChaseState::execute(Entity *owner, double dt) noexcept
{
	auto g = owner->get_components<PhysicsComponent>()[0];



	if (!length(owner->getPosition() - _player->getPosition()) < 300.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("chase");
	}

	if (_player->getPosition().x > owner->getPosition().x)
	{
		owner->get_components<AnimationComponent>()[0]->faceRight = true;
		g->impulse({ 5.0f , 0.0f });
		g->dampen({ 0.7f , 1.0f });
	}

	//follow left
	if (_player->getPosition().x < owner->getPosition().x)
	{
		owner->get_components<AnimationComponent>()[0]->faceRight = false;
		g->impulse({ -5.0f , 0.0f });
		g->dampen({ 0.7f , 1.0f });

	}

}

void  Goblin_AttackState::execute(Entity *owner, double dt) noexcept
{
	if (!length(owner->getPosition() - _player->getPosition()) < 300.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("Idle");
	}
}