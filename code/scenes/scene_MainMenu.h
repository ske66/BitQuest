#pragma once

#include "engine.h"
#include <SFML\Audio.hpp>

class MainMenuScene : public Scene {
public:
	MainMenuScene() = default;
	~MainMenuScene() override = default;

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;

private:

	std::shared_ptr<sf::Music>_musicMenu;

	std::shared_ptr<Entity> _btnNewGame;
	std::shared_ptr<Entity> _btnLoadGame;
	std::shared_ptr<Entity> _btnSettings;
	std::shared_ptr<Entity> _btnExit;

	std::vector<std::shared_ptr<Entity>> _btns;
};