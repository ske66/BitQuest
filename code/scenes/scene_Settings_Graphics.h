#pragma once

#include "engine.h"

class SettingsGraphicsScene : public Scene {
public:
	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;

private:

	std::shared_ptr<Entity> _btnBack;
	std::shared_ptr<Entity> _btnDone;

	std::shared_ptr<Entity> _ResLow;
	std::shared_ptr<Entity> _ResMed;
	std::shared_ptr<Entity> _ResHigh;
	std::shared_ptr<Entity> _btnOn;
	std::shared_ptr<Entity> _btnOff;
	std::shared_ptr<Entity> _btn30;
	std::shared_ptr<Entity> _btn60;

	std::vector<std::shared_ptr<Entity>> _btns;

	float _clickCooldown;

	std::shared_ptr<Entity> _changingGraphics = nullptr;

	bool settingSelected = false;

};