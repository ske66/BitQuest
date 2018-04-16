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
std::shared_ptr<Entity> makeArrow();

std::vector<std::shared_ptr<Entity>> makeEnemies();
std::vector<std::shared_ptr<Entity>> makeShops();
std::vector<std::shared_ptr<Entity>> makeTorches();
std::shared_ptr<Entity> makeCoin();
std::vector<std::shared_ptr<Entity>> makeChests();
std::shared_ptr<Entity> makeEventBox(sf::Vector2f bounds);


void TilePhysics();
