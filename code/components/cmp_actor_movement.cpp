#include "cmp_actor_movement.h"
#include <LevelSystem.h>

using namespace sf;

void ActorMovementComponent::update(double dt) {}

ActorMovementComponent::ActorMovementComponent(Entity* p)
	: Component(p) {}

bool ActorMovementComponent::validMove(const sf::Vector2f& pos)
{
	//return (LevelSystem::getTileAt(pos) != LevelSystem::WALL);  // needs tile map to work properly
	return true;
}

void ActorMovementComponent::move(const sf::Vector2f& p)
{
	auto pp = _parent->getPosition() + p;

		if (validMove(pp))
		{
			_parent->setPosition(pp);

		}
}

void ActorMovementComponent::move(float x, float y)
{
	move(Vector2f(x, y));
}

