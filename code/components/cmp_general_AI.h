
#pragma once

#include "ecm.h"
#include "engine.h"
#include "cmp_gavin_physics.h"
#include <SFML/Window/Keyboard.hpp>
#include "cmp_animation.h"
#include "cmp_state.h"

class GeneralAiComponent : public Component
{
protected:
	double totaltime;
	double attackspeed;
	double movementspeed;

public:

	GeneralAiComponent() = delete;

	void moveToPlayer();
	explicit GeneralAiComponent(Entity* p);
	bool checkInRange(int range);

	void update(double dt);
	void render() override;

};
