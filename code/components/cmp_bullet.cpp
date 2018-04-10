#include "cmp_bullet.h"
#include "engine.h"
#include <iostream>
#include <chrono>


BulletComponent::BulletComponent(Entity* p)
	: Component(p)
{



	if (!(length(_parent->setPosition().x - _parent->scene->ents.find("gavin")[0]->getPosition().x) < 150.0f))
	{

	}

	

}
