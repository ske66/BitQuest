#include "cmp_troll_properties.h"
#include "cmp_player_physics.h"
#include "cmp_player_controller.h"
#include <iostream>


TrollPropertiesComponent::TrollPropertiesComponent(Entity* p)
	: Component(p)
{
	_player = _parent->scene->ents.find("player")[0];

}


void TrollPropertiesComponent::takeDamage(double h)
{

	if (immortal == false)
	{
		immortal = true;
		_health = _health - h;

	}

}

double TrollPropertiesComponent::getHealth()
{
	return _health;
}

void TrollPropertiesComponent::update(double dt)
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

void TrollPropertiesComponent::render()
{

}

void TrollPropertiesComponent::checkContact(double dt)
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
				takeDamage(ap->playerDamage);
			}	
			if (_parent->get_components<AnimationComponent>()[0]->attackImgNo >= 5)
			{
				ap->takeDamage(trollDamage, dt);
			}
				
			

		}
	}

}

void TrollPropertiesComponent::checkHealth()
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