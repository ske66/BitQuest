#include "cmp_player_controller.h"


PlayerControlerComponent::PlayerControlerComponent(Entity* p)
	: Component(p)
{

}

double PlayerControlerComponent::getHealth()
{
	return _health;
}
void PlayerControlerComponent::setHealth(double b)
{
	_health = b;
}

int PlayerControlerComponent::getCoins()
{
	return coins;
}
void PlayerControlerComponent::collectCoin()
{
	coins += 1;
}


void PlayerControlerComponent::update(double dt)
{
	auto me = _parent->get_components<StateComponent>()[0];
	auto me_anim = _parent->get_components<AnimationComponent>()[0];
	auto me_pys = _parent->get_components<PlayerPhysicsComponent>()[0];

	if (me->getAttacking() != true)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			
			me->setWalkingLeft();
			me_pys->MoveLeft(dt); 
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				me->setAttacking();
				me_pys->setVelocity({ 0.0 , 0.0 });
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			me->setWalkingRight();
			me_pys->MoveRight(dt);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				me->setAttacking();
				me_pys->setVelocity({ 0.0 , 0.0 });
			}
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			me->setAttacking();

		}
		else
		{
			me_pys->dampen({ 0.7f , 1.0f });
		}
	}
	collisionCheck();
}


void PlayerControlerComponent::render()
{

}
void PlayerControlerComponent::takeDamage(double d)
{
	_health = _health - d;
}
void PlayerControlerComponent::collisionCheck()
{
	auto g = _parent->scene->ents.find("gavin")[0];
	auto gavin = g->get_components<StateComponent>()[0];
	auto coins = _parent->scene->ents.find("coin");
	auto cs = _parent->get_components<PlayerPhysicsComponent>()[0]->getTouching();


	for (auto c : cs)
	{
		if (c->GetFixtureB() == g->get_components<GavinPhysicsComponent>()[0]->getFixture())
		{
			if (gavin->getAttacking() == true)
			{

				takeDamage(1.0);
			}

		}

		for (auto b : coins)
		{
			if (c->GetFixtureA() == b->get_components<PhysicsComponent>()[0]->getFixture())
			{
				collectCoin();
				b->setForDelete();
			}

		}


	}

}