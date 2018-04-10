#include "cmp_bullet.h"
#include "engine.h"
#include "cmp_player_physics.h"
#include <iostream>
#include <chrono>
#include <string>

BulletComponent::BulletComponent(Entity* p)
	: Component(p)
{
	_bulletSpeed = 1000;

}

void BulletComponent::update(double dt)
{
	moveBullet(dt);
}
void BulletComponent::render()
{}

void BulletComponent::moveBullet(double dt)
{
	if (_parent->getPosition().x > _parent->scene->ents.find("player")[0]->getPosition().x)
	{
		_parent->setPosition(sf::Vector2f(_parent->get_components<SpriteComponent>()[0]->getSprite().getPosition().x + 0.00001,
			_parent->get_components<SpriteComponent>()[0]->getSprite().getPosition().y));
	}
	else if (_parent->getPosition().x < _parent->scene->ents.find("player")[0]->getPosition().x)
	{

		_parent->setPosition(sf::Vector2f(_parent->getPosition().x - 0.000000000001, 0 ));
	}

}


