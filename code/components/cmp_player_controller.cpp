#include "cmp_player_controller.h"
#include "cmp_state_Machine.h"
#include "cmp_UI.h"
#include "cmp_text.h"
#include "../code/GameState.h"

using namespace std;
using namespace sf;

PlayerControlerComponent::PlayerControlerComponent(Entity* p)
	: Component(p)
{
	playerDamage = 1;
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
	coins++;

	_parent->scene->ents.find("coinCount")[0]->get_components<TextComponent>()[0]->SetText("x" + to_string(coins));
}




void PlayerControlerComponent::update(double dt)
{
	auto UI = _parent->scene->ents.find("UI")[0]->get_components<UIComponent>()[0];

	if (UI->sword == true)
	{
		sword = true;
	}
	else
	{
		sword = false;
	}

	
		UI->setHealthDisplay(checkHealth());
		collisionCheck(dt);

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

sf::IntRect PlayerControlerComponent::checkHealth()
{
	
	if (_health == 10)
	{
		return sf::IntRect(0, 0, 400, 50);
	}

	if (_health == 9)
	{
		return sf::IntRect(0, 0, 360, 50);
	}
	if (_health == 8)
	{
		return sf::IntRect(0, 0, 320, 50);
	}

	if (_health == 7)
	{
		return sf::IntRect(0, 0, 280, 50);
	}
	if (_health == 6)
	{
		return sf::IntRect(0, 0, 240, 50);
	}

	if (_health == 5)
	{
		return sf::IntRect(0, 0, 200, 50);
	}
	if (_health == 4)
	{
		return sf::IntRect(0, 0, 160, 50);
	}

	if (_health == 3)
	{
		return sf::IntRect(0, 0, 120, 50);
	}
	if (_health == 2)
	{
		return sf::IntRect(0, 0, 80, 50);
	}

	if (_health == 1)
	{
		return sf::IntRect(0, 0, 40, 50);
	}
	if (_health == 0)
	{
		return sf::IntRect(0, 0, 0, 50);
	}

}


void PlayerControlerComponent::render()
{

}
void PlayerControlerComponent::takeDamage(double d , double dt)
{	
	if (immortal == false)
	{
		immortal = true;
		_health = _health - d;

		_bufferHit = *(Resources::get<SoundBuffer>("Bob_Sounds/Bob_Hit.wav"));
		_soundHit.setBuffer(_bufferHit);

		_soundHit.play();
		_soundHit.setVolume(sfxVolume);
	}
		
}


void PlayerControlerComponent::collisionCheck(double dt)
{
	auto coins = _parent->scene->ents.find("coin");
	auto cs = _parent->get_components<PlayerPhysicsComponent>()[0]->getTouching();

	for (auto c : cs)
	{
		for (auto b : coins)
		{
			if (c->GetFixtureB() == b->get_components<PhysicsComponent>()[0]->getFixture())
			{
				collectCoin();
				b->setForDelete();
			}

		}
		
	}

}