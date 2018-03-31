#pragma once

#include "ecm.h"
#include <string>

std::shared_ptr<Entity> makeButton(std::string, sf::Vector2f bounds);
std::shared_ptr<Entity> makePlayer();
std::shared_ptr<Entity> makeGavin();
std::shared_ptr<Entity> makeTorch();
std::vector<std::shared_ptr<Entity>> makeEnemies();
std::vector<std::shared_ptr<Entity>> makeCoin();

void TilePhysics();
