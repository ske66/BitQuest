#include "cmp_enemy_AI.h"


using namespace std;



GavinAiComponent::GavinAiComponent(Entity* p)
	: Component(p)
{
	attackspeed = 0.1;
	totaltime = 0.0;
}

void GavinAiComponent::update(double dt) 
{
	auto p = _parent->scene->ents.find("player")[0];

	totaltime += dt;

	if (totaltime >= attackspeed)
	{
		totaltime -= attackspeed;

		if (_parent->getState() != "attack")
		{
			std::cout << "attack mode" << std::endl;
			_parent->setState("attack");
			return;
		}
		else
		{
			std::cout << "standby" << std::endl;
			_parent->setState("");
		}
	}
}

void GavinAiComponent::render() {  }





