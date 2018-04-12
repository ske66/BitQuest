#pragma once

#include <ecm.h>
#include "SFML\Graphics.hpp"
#include "cmp_animation.h"

class UIComponent : public Component
{
private:

	sf::RectangleShape weaponSelection;

	std::shared_ptr<sf::Texture> _texHeartUI;
	std::shared_ptr<sf::Texture> _texCoinUI;
	std::shared_ptr<sf::Texture> _texArrowUI;
	std::shared_ptr<sf::Texture> _texSwordUI;
	std::shared_ptr<sf::Texture> _texBowUI;

	sf::Sprite heartUI;
	sf::Sprite coinUI;
	sf::Sprite arrowUI;
	sf::Sprite weaponUI;

	std::shared_ptr<Entity> _coinCount;
	std::shared_ptr<Entity> _arrowCount;


public:
	UIComponent() = delete;
	void setHealthDisplay(sf::IntRect s);
	explicit UIComponent(Entity* p);
	void update(double dt) override;
	void render() override;
};