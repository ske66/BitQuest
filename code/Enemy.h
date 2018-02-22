#pragma once
#include "ecm.h"

using namespace sf;

class Enemy : public Entity {
private:
	float _speed;

public:
	void update(const float dt) override;
	Enemy();
	void render(sf::RenderWindow &window) const override;
};