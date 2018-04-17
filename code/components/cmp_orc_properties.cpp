
#include "cmp_physics.h"
#include "cmp_player_physics.h"
#include "cmp_player_controller.h"
#include "cmp_orc_properties.h"


OrcPropertiesComponent::OrcPropertiesComponent(Entity* p)
	: Component(p)
{
	_player = _parent->scene->ents.find("player")[0];
};

void OrcPropertiesComponent::takeDamage(double h)
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
		this->checkHealth();
	}
}

double OrcPropertiesComponent::getHealth()
{
	return _health;
}

void OrcPropertiesComponent::update(double dt)
{
	if (length(_parent->getPosition() - _player->getPosition()) < 300)
	{
		this->checkContact(dt);
	}

	_parent->get_components<SpriteComponent>()[0]->Sprite("EnemyHealth.png", rect);

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

void OrcPropertiesComponent::render()
{

}

void OrcPropertiesComponent::checkContact(double dt)
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
					this->takeDamage(ap->playerDamage);
				}
				
			}
			if (_parent->get_components<AnimationComponent>()[0]->attackImgNo >= 5)
			{
				ap->takeDamage(orcDamage, dt);
			}
		}
	}

}
sf::IntRect OrcPropertiesComponent::checkHealth()
{
	if (_health == 4)
	{
		rect = sf::IntRect(0, 0, 100, 5);
	}

	if (_health == 3)
	{
		rect = sf::IntRect(0, 0, 75, 5);
	}

	if (_health == 2)
	{
		rect = sf::IntRect(0, 0, 50, 5);
	}

	if (_health == 1)
	{
		rect = sf::IntRect(0, 0, 25, 5);
	}
	if (_health == 0)
	{
		rect = sf::IntRect(0, 0, 0, 5);
	}

	return rect;

}