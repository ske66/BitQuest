#pragma once

#include "engine.h"
#include <SFML\Audio.hpp>

class ShopScene : public Scene {
public:
	ShopScene() = default;
	~ShopScene() override = default;

	void Load() override;

	void UnLoad() override;

	void Update(const double& dt) override;

	void Render() override;

private:

	std::shared_ptr<sf::Music>_musicShop;
};