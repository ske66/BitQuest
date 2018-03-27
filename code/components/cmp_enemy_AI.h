#pragma once
#include "ecm.h"
#include "engine.h"
#include <SFML/Window/Keyboard.hpp>

class GavinAiComponent : public Component 
{
protected:
	double totaltime;
	double attackspeed;

public:

	GavinAiComponent() = delete;


	explicit GavinAiComponent(Entity* p);

	void update(double dt);
	void render() override;


};
