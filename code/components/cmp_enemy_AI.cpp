<<<<<<< HEAD
#include "cmp_enemy_AI.h"

=======

/*
#include "cmp_enemy_ai.h"
>>>>>>> b5ffb189b6edb982915f3ae3dc8ba305200e1e51

using namespace std;



<<<<<<< HEAD
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





=======
	sf::Vector2f direction = { 0.0f, 0.0f };
	
	direction.x = rand() % 2 + 0 - 1;
	
	
	
	move((float)dt * direction * _speed);

}

*/
>>>>>>> b5ffb189b6edb982915f3ae3dc8ba305200e1e51
