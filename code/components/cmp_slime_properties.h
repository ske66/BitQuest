
#pragma once
#include <ecm.h>
#include "engine.h"
#include <SFML/Audio.hpp>

class SlimePropertiesComponent : public Component
{
protected:
	float _health = 4;
	float damageDelay = 0.5;
	float totalTime = 0;

public:

	sf::SoundBuffer _bufferHit;
	sf::SoundBuffer _bufferDeath;

	sf::Sound _soundHit;
	sf::Sound _soundDeath;

	sf::IntRect rect;
	bool immortal = true;
	float slimeDamage = 3;
	std::vector<std::shared_ptr<Entity>> _trolls;
	std::shared_ptr<Entity> _player;
	explicit SlimePropertiesComponent(Entity* p);
	sf::IntRect checkHealth();
	SlimePropertiesComponent() = delete;
	double getHealth();
	void takeDamage(double);
	void update(double dt);
	void render() override;
	void checkContact(double dt);
};