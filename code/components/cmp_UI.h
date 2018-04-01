#pragma once

#include <ecm.h>
#include "SFML\Graphics.hpp"
#include "cmp_animation.h"

class UIComponent : public Component
{
private:
	sf::RectangleShape topBar;
	sf::RectangleShape bottomBar;
	std::shared_ptr<Entity> health();

public:
	UIComponent() = delete;
	explicit UIComponent(Entity* p);
	void update(double dt) override;
	void render() override;
};