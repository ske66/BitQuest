#pragma once

#include "Entity.h"

using namespace sf;

class Player : public Entity {
private:
	float _speed;

public:
	void update(const float dt) override;
	Player();
	void render(sf::RenderWindow &window) const override;
};