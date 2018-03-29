#pragma once
#include "ecm.h"
#include "engine.h"
#include "cmp_gavin_physics.h"
#include <SFML/Window/Keyboard.hpp>
#include "cmp_animation.h"
#include "cmp_state.h"

class GavinAiComponent : public Component
{
protected:
	double totaltime;
	double attackspeed;
	double movementspeed;

public:

	GavinAiComponent() = delete;

	void moveToPlayer();
	explicit GavinAiComponent(Entity* p);
	bool checkInRange(int range);

	void update(double dt);
	void render() override;

};
