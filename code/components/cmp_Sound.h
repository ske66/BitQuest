/*

#pragma once

#include "ecm.h"
#include "SFML\Audio.hpp"

class SoundComponent : public Component {
protected:
	std::shared_ptr<sf::Sound> _sound;
	int b;

public:

	SoundComponent() = delete;

	void Sound(std::string a, int b);

	explicit SoundComponent(Entity* p);
	void update(double dt) override;

	sf::Sound& getSound() const;

	template <typename... Targs> void setSound(Targs... params)
	{
		_sound.reset(new sf::Sound(params...));
	}
};

*/