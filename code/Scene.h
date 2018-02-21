#pragma once

#include "Entity.h"
#include <memory>

class Scene {
public:
	Scene() = default;

	virtual ~Scene() = default;
	virtual void update(const float dt);
	virtual void render();
	virtual void load() = 0;
	std::vector<std::shared_ptr<Entity>> &getEnts();

protected:
	EntityManager _ents;
};