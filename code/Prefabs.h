#pragma once

#include "ecm.h"
#include <string>

std::shared_ptr<Entity> makeButton(std::string, sf::Vector2f bounds);
std::shared_ptr<Entity> makePlayer(sf::Vector2f _pos);
std::shared_ptr<Entity> makeGavin();
std::shared_ptr<Entity> addUI();
std::shared_ptr<Entity> GavinBlast();
std::shared_ptr<Entity> coinAmount();
std::shared_ptr<Entity> arrowAmount();
std::shared_ptr<Entity> playerArrow();

std::vector<std::shared_ptr<Entity>> makeEnemies();
std::vector<std::shared_ptr<Entity>> makeShops();
std::vector<std::shared_ptr<Entity>> makeTorches();
std::vector<std::shared_ptr<Entity>> makeCoins();
std::vector<std::shared_ptr<Entity>> makeChests();


void TilePhysics();
