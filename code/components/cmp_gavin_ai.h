#pragma once
#include <ecm.h>

class GavinAiComponent : public Component
{
protected:

public:
	explicit GavinAiComponent(Entity* p);
	GavinAiComponent() = delete;
	

	void render() override {};
	void update(double dt);
		
};
