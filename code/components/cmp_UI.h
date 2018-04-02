#pragma once

#include <ecm.h>
#include "SFML\Graphics.hpp"
#include "cmp_animation.h"

class UIComponent : public Component
{
private:

	std::shared_ptr<sf::Texture> _texHeartUI;
	std::shared_ptr<sf::Texture> _texCoinUI;

	sf::Sprite heartUI;
	sf::Sprite coinUI;

	sf::RectangleShape topBar;

	int currentHealth = 180;

public:
	UIComponent() = delete;
	explicit UIComponent(Entity* p);
	void update(double dt) override;
	void render() override;
};