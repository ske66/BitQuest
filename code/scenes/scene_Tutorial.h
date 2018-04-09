#pragma once

#include "engine.h"

class TutorialScene : public Scene {
public:
	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;

private:
	std::shared_ptr<Entity> _player;
	sf::Vector2f _view_center;

};