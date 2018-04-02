#pragma once

#include "ecm.h"
#include <string>

std::shared_ptr<Entity> makeButton(std::string, sf::Vector2f bounds);
std::shared_ptr<Entity> makePlayer();
std::shared_ptr<Entity> makeGavin();
std::shared_ptr<Entity> addUI();

std::vector<std::shared_ptr<Entity>> makeTorches();
std::vector<std::shared_ptr<Entity>> makeEnemies();
std::vector<std::shared_ptr<Entity>> makeShops();
std::vector<std::shared_ptr<Entity>> makeCoin();
std::vector<std::shared_ptr<Entity>> makeChest();

void TilePhysics();
