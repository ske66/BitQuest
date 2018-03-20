#pragma once

#include "engine.h"

class MainMenuScene : public Scene {
public:
	MainMenuScene() = default;
	~MainMenuScene() override = default;

	void Load() override;

	void Update(const double& dt) override;
};