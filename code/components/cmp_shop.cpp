#include "cmp_shop.h"
#include "cmp_text.h"
#include "../code/GameState.h"
#include "engine.h"
#include <SFML\Window.hpp>

using namespace std;

ShopComponent::ShopComponent(Entity *p)
	: Component(p)
{
	totaltime = 0.f;
	switchtime = 2.5f;
	currentline = 0;
}

void ShopComponent::update(double dt)
{

	auto shop = _parent->scene->ents.find("Shop")[0];
	auto t = shop->addComponent<TextComponent>();
	t->getText().setCharacterSize(16);
	t->getText().setOrigin(60, 40);
	
	string talk;
	const string talk_cols[]{ "Press Enter to open shop!","We've got stuff that you can use!","Upgrades and food for all heroes!","Buy all the stuff you need!", "I need money for my family!", "Please buy my stuff!","Better than Ebay and Etsy!", "This is a test", "This is not a test", "This is scripted, we don't make mistakes..." };
	
	if (checkInRange(400) == true)
	{
		
		totaltime += dt;

		if (totaltime >= switchtime)
		{
			totaltime -= switchtime;
			currentline++;
		
			if (currentline >= 10)
			{
				currentline = 0;
			}
		}
		
		_parent->get_components<TextComponent>()[0]->SetText(talk_cols[currentline]);
		
	}
	else if (checkInRange(400) == false)
	{
		_parent->get_components<TextComponent>()[0]->SetText("");
	}
	
}

bool ShopComponent::checkInRange(int range)
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

void ShopComponent::render() {}
