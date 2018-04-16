#include "cmp_ghost_properties.h"
#include "cmp_player_physics.h"
#include "cmp_physics.h"
#include "cmp_player_controller.h"
#include <iostream>


GhostPropertiesComponent::GhostPropertiesComponent(Entity* p)
	: Component(p)
{
	_player = _parent->scene->ents.find("player")[0];

}


void GhostPropertiesComponent::takeDamage(double h)
{

	if (immortal == false)
	{
		immortal = true;
		if (_player->getPosition().x < _parent->getPosition().x)
		{
			_parent->get_components<PhysicsComponent>()[0]->getFixture()->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(20.f, 0.f), true);
		}
		else
		{
			_parent->get_components<PhysicsComponent>()[0]->getFixture()->GetBody()->ApplyLinearImpulseToCenter(b2Vec2(-20.f, 0.f), true);
		}
		_health = _health - h;
		
	}
	
}

double GhostPropertiesComponent::getHealth()
{
	return _health;
}

void GhostPropertiesComponent::update(double dt)
{
	
	//only check when near player (saves performance evaluation of position Runs in Constant time loop runs in liniar time avoid where possible)
	if (length(_parent->getPosition() - _player->getPosition()) > 50)
	{
		this->checkContact();
	}

	_parent->get_components<SpriteComponent>()[0]->Sprite("EnemyHealth.png", rect);


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

void GhostPropertiesComponent::render()
{

}

void GhostPropertiesComponent::checkContact()
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
					if (_player->get_components<AnimationComponent>()[0]->attackImgNo > 5)
					{
						this->takeDamage(ap->playerDamage);
					}
				}
				
			}
		}

}

void GhostPropertiesComponent::checkHealth()
{
	auto bar = _parent->get_components<SpriteComponent>()[0];

	if (_health == 2)
	{
		rect = sf::IntRect(0, 0, 100, 5);
	}

	if (_health == 1)
	{
		rect = sf::IntRect(0, 0, 50, 5);
	}
	if (_health == 0)
	{
		rect = (sf::IntRect(0, 0, 0, 5));
	}

}