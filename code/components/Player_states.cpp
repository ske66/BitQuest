
#include "prefabs.h"
#include <random>
#include <chrono>
#include "components/cmp_sprite.h"
#include "components/cmp_animation.h"
#include <iostream>


using namespace sf;
using namespace std;

float _timer = 1.0f;
// Gavin ----------------------------------------------------------------------

void  Player_IdleState::execute(Entity *owner, double dt) noexcept
{
	// Don't move
	owner->get_components<GavinPhysicsComponent>()[0]->setVelocity(Vector2f(0, 0));


	//Chase player when in range
	if (length(owner->getPosition() - _player->getPosition()) < 400.0f)
	{
		auto sm = owner->get_components<StateMachineComponent>()[0];
		sm->changeState("chase");
	}
}