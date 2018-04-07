#include "cmp_player_controller.h"
#include "cmp_state_Machine.h"

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
	auto gavin = g->get_components<StateMachineComponent>()[0];
	auto coins = _parent->scene->ents.find("coin");
	auto cs = _parent->get_components<PlayerPhysicsComponent>()[0]->getTouching();


	for (auto c : cs)
	{
		if (c->GetFixtureB() == g->get_components<GavinPhysicsComponent>()[0]->getFixture())
		{
			if (gavin->getState("Attack") != nullptr)
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