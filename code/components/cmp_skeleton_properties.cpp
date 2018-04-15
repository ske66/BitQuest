#include "cmp_skeleton_properties.h"
#include "cmp_player_physics.h"
#include "cmp_player_controller.h"
#include <iostream>


SkeletonPropertiesComponent::SkeletonPropertiesComponent(Entity* p)
	: Component(p)
{
	_player = _parent->scene->ents.find("player")[0];

}


void SkeletonPropertiesComponent::takeDamage(double h)
{

	if (immortal == false)
	{
		if (_player->getPosition().x < _parent->getPosition().x)
		{
			_parent->get_components<PhysicsComponent>()[0]->getFixture()->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(40.f, 0.f), true);
		}
		else
		{
			_parent->get_components<PhysicsComponent>()[0]->getFixture()->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(-40.f, 0.f), true);
		}
		immortal = true;
		_health = _health - h;

	}

}

double SkeletonPropertiesComponent::getHealth()
{
	return _health;
}

void SkeletonPropertiesComponent::update(double dt)
{

	//only check when near player (saves performance evaluation of position Runs in Constant time loop runs in liniar time avoid where possible)
	if (length(_parent->getPosition() - _player->getPosition()) > 50)
	{
		checkContact(dt);
	}

	checkHealth();
	if (immortal == true)
	{
		totalTime += dt;

		if (totalTime >= damageDelay)
		{
			totalTime -= damageDelay;
			immortal = false;
		}
	}
}

void SkeletonPropertiesComponent::render()
{

}

void SkeletonPropertiesComponent::checkContact(double dt)
{

	auto cs = _parent->get_components<PhysicsComponent>()[0]->getTouching();

	auto ap = _player->get_components<PlayerControlerComponent>()[0];
	auto playerPhys = _player->get_components<PlayerPhysicsComponent>()[0];

	for (auto c : cs)
	{
		if (c->GetFixtureA() == playerPhys->getFixture() || c->GetFixtureB() == playerPhys->getFixture())
		{
			if (_player->get_components<StateMachineComponent>()[0]->currentState() == "Attack")
			{
				if (_player->get_components<AnimationComponent>()[0]->attackImgNo >= 6)
				{
					takeDamage(ap->playerDamage);
				}
			}	
			if (_parent->get_components<AnimationComponent>()[0]->attackImgNo >= 5)
			{
				ap->takeDamage(skeletonDamage, dt);
			}
				
			

		}
	}

}

void SkeletonPropertiesComponent::checkHealth()
{
	auto bar = _parent->get_components<SpriteComponent>()[0];

	if (_health == 10)
	{
		bar->getSprite().setTextureRect(sf::IntRect(0, 0, 100, 5));
	}

	if (_health == 9)
	{
		bar->getSprite().setTextureRect(sf::IntRect(0, 0, 90, 5));
	}
	if (_health == 8)
	{
		bar->getSprite().setTextureRect(sf::IntRect(0, 0, 80, 5));
	}

	if (_health == 7)
	{
		bar->getSprite().setTextureRect(sf::IntRect(0, 0, 70, 5));
	}
	if (_health == 6)
	{
		bar->getSprite().setTextureRect(sf::IntRect(0, 0, 60, 5));
	}

	if (_health == 5)
	{
		bar->getSprite().setTextureRect(sf::IntRect(0, 0, 50, 5));
	}
	if (_health == 4)
	{
		bar->getSprite().setTextureRect(sf::IntRect(0, 0, 40, 5));
	}

	if (_health == 3)
	{
		bar->getSprite().setTextureRect(sf::IntRect(0, 0, 30, 5));
	}

	if (_health == 2)
	{
		bar->getSprite().setTextureRect(sf::IntRect(0, 0, 20, 5));
	}

	if (_health == 1)
	{
		bar->getSprite().setTextureRect(sf::IntRect(0, 0, 10, 5));
	}
	if (_health == 0)
	{
		bar->getSprite().setTextureRect(sf::IntRect(0, 0, 0, 5));
	}

}