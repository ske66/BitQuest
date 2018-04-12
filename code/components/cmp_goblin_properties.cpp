#include "cmp_goblin_properties.h"
#include "cmp_physics.h"
#include "cmp_player_physics.h"
#include "cmp_player_controller.h"

GoblinPropertiesComponent::GoblinPropertiesComponent(Entity* p)
	: Component(p)
{
	_player = _parent->scene->ents.find("player")[0];
};

void GoblinPropertiesComponent::takeDamage(double h)
{
	if (immortal == false)
	{
		immortal = true;
		_health = _health - h;
		this->checkHealth();
	}
}

double GoblinPropertiesComponent::getHealth()
{
	return _health;
}


void GoblinPropertiesComponent::update(double dt)
{
	if (length(_parent->getPosition() - _player->getPosition()) < 100)
	{
		this->checkContact(dt);
	}

	

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
void GoblinPropertiesComponent::render()
{

}
void GoblinPropertiesComponent::checkContact(double dt)
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
				std::cout << _health << std::endl;
				this->takeDamage(ap->playerDamage);
			}
			else
			{
				ap->takeDamage(goblinDamage, dt);
			}
		}
	}

}

void GoblinPropertiesComponent::checkHealth()
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