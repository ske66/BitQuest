/*

#include "cmp_Sound.h"
#include <iostream>
#include <System_Renderer.h>
#include <system_resources.h>

using namespace std;

void SoundComponent::Sound(std::string a, int b)
{
	_sound = Resources::get<sf::Sound>(a);
	this->b = b;

	
}

SoundComponent::SoundComponent(Entity* p)
	: Component(p), _sound(make_shared<sf::Sound>())
{

}

void SoundComponent::update(double dt)
{
	_sound->setVolume(b);
	_sound->play();

}

sf::Sound& SoundComponent::getSound() const { return *_sound; }

*/