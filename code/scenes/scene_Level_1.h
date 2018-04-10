#pragma once

#include "engine.h"

class Level1Scene : public Scene {
public:
	double holdTime = 2;
	double totalTime = 0;

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;
};