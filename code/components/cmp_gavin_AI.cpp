#include "cmp_gavin_AI.h"


using namespace std;




GavinAiComponent::GavinAiComponent(Entity* p)
	: Component(p)
{


	attackspeed = 2.0f;
	totaltime = 0.0;

}


void GavinAiComponent::update(double dt)
{
	/*
	totaltime += dt;

	if (_parent->get_components<StateComponent>()[0]->getAttacking() != true)
	{
	if (checkInRange(200))
	{
	if (totaltime >= attackspeed)
	{
	totaltime -= attackspeed;

	_parent->get_components<StateComponent>()[0]->setAttacking();
	}

	}
	else if (checkInRange(400) == true)
	{
	moveToPlayer();
	}
	if (checkInRange(400) == false)
	{

	_parent->get_components<StateComponent>()[0]->setIdle();
	}
	}
	*/
}

bool GavinAiComponent::checkInRange(int range)
{
	auto player = _parent->scene->ents.find("player")[0];

	if (player->getPosition().x >= _parent->getPosition().x - range && player->getPosition().x <= _parent->getPosition().x)
	{
		return true;
	}
	if (player->getPosition().x <= _parent->getPosition().x + range && player->getPosition().x >= _parent->getPosition().x)
	{
		return true;
	}
	return false;
}


void GavinAiComponent::render() {  }
