#pragma once

#include "ecm.h"
#include <string>

std::shared_ptr<Entity> makeButton(std::string, sf::Vector2f bounds);
std::shared_ptr<Entity> makePlayer(sf::Vector2f _pos);
std::shared_ptr<Entity> makeGavin();
std::shared_ptr<Entity> addUI(std::string message);
std::shared_ptr<Entity> GavinBlast();
std::shared_ptr<Entity> makeArrow();

std::shared_ptr<Entity> slimeBlast();
std::shared_ptr<Entity> ghostBlast();

std::shared_ptr<Entity> makeCoin(sf::Vector2f pos);

std::vector<std::shared_ptr<Entity>> makeEnemies();
std::vector<std::shared_ptr<Entity>> makeShops();
std::vector<std::shared_ptr<Entity>> makeTorches();
std::vector<std::shared_ptr<Entity>> makeChests();
std::shared_ptr<Entity> makeEventBox(sf::Vector2f bounds);


void TilePhysics();
