#pragma once

#include "ecm.h"
#include "System_Renderer.h"
#include <memory>

class Scene {
public:
	Scene() = default;

	virtual ~Scene() = default;
	virtual void update(float dt);
	virtual void render();
	virtual void load() = 0;
	std::vector<std::shared_ptr<Entity>> &getEnts();

protected:
	EntityManager _ents;
};