#pragma once

#include "ecm.h"
#include "engine.h"
#include "cmp_gavin_physics.h"
#include <SFML/Window/Keyboard.hpp>
#include "cmp_animation.h"
#include "cmp_state.h"

class ShopComponent : public Component
{
protected:

	bool inRange = false;

public:

	double totaltime;
	double switchtime;
	int currentline;

	ShopComponent() = delete;

	explicit ShopComponent(Entity* p);
	bool checkInRange(int range);

	void update(double dt);
	void render() override;
};