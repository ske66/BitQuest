#pragma once
#include "engine.h"
#include <map>


class SettingsGameplayScene : public Scene {
public:
	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;

private:
	std::shared_ptr<Entity> _btn_ControlsAction;
	std::shared_ptr<Entity> _btn_ControlsLeft;
	std::shared_ptr<Entity> _btn_ControlsRight;
	std::shared_ptr<Entity> _btn_ControlsJump;
	std::shared_ptr<Entity> _btn_ControlsAttack;
	std::shared_ptr<Entity> _btn_ControlsBlock;
	std::shared_ptr<Entity> _btn_ControlsSword;
	std::shared_ptr<Entity> _btn_ControlsBow;
	std::shared_ptr<Entity> _btn_Back;
	std::shared_ptr<Entity> _btn_Done;

	std::vector<std::shared_ptr<Entity>> _btns;

	std::map<std::shared_ptr<Entity>, std::string> _controlsBtns;

	std::shared_ptr<Entity> _changingControl = nullptr;


	float _clickCooldown;

};