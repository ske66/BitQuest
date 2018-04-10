/*
#include "cmp_hurt.h"
#include "system_physics.h"
#include "engine.h"
#include "cmp_physics.h"
#include "cmp_player_controller.h"
#include "cmp_gavin_properties.h"

using namespace std;
using namespace sf;

HurtComponent::HurtComponent(Entity* p, string tagToHurt)
	: Component(p), _tagToHurt(tagToHurt), _active(false)
{

}

void HurtComponent::update(double dt)
{

	_isHurting = false;

	if (_active)
	{
		if (_parent->getTags() == _parent->scene->ents.find("player")[0]->getTags())
		{
			auto cs = _parent->get_components<PlayerPhysicsComponent>()[0]->getTouching();

			for (auto c : cs)
			{
				auto entsToHurt = Engine::GetActiveScene()->ents.find(_tagToHurt);
				for (auto entityToHurt : entsToHurt)
				{
					if (c->GetFixtureA() == entityToHurt->get_components<PlayerPhysicsComponent>()[0]->getFixture() ||
						c->GetFixtureB() == entityToHurt->get_components<PlayerPhysicsComponent>()[0]->getFixture())
					{
						cout << "dmg" << endl;
					//	if (_tagToHurt == "player") entityToHurt->get_components<PlayerControlerComponent>()[0]->takeDamage(_damage);
						else if (_tagToHurt == "gavin") entityToHurt->get_components<GavinPropertiesComponent>()[0]->takeDamage(_damage);
						_isHurting = true;
					}
				}
			}
		}
		else
		{
			auto cs = _parent->get_components<PhysicsComponent>()[0]->getTouching();
			for (auto c : cs)
			{
				auto entsToHurt = Engine::GetActiveScene()->ents.find(_tagToHurt);
				for (auto entityToHurt : entsToHurt)
				{
					if (c->GetFixtureA() == entityToHurt->get_components<PhysicsComponent>()[0]->getFixture() ||
						c->GetFixtureB() == entityToHurt->get_components<PhysicsComponent>()[0]->getFixture())
					{
						cout << "dmg" << endl;
						if (_tagToHurt == "gavin") entityToHurt->get_components<GavinPropertiesComponent>()[0]->takeDamage(_damage);
						_isHurting = true;
					}
				}
			}
		}
	}
}

void HurtComponent::setDamage(int d) { _damage = d; }

void HurtComponent::setActive(bool a) { _active = a; }

bool HurtComponent::isHurting() { return _isHurting; }
*/