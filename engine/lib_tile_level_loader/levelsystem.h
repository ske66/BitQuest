#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include "maths.h"

#define ls LevelSystem

class LevelSystem {
public:
	static void loadLevelFile(const std::string&, float tileSize = 100.f);
	static void unload();
	static void render(sf::RenderWindow &window);

	typedef unsigned char Tile;

	enum TILES { 
		EMPTY = ' ',
		GROUND = 'g',
		START = 's',
		END = 'e', 
		WALL = 'w',
		FLOOR = 'f',
		ENEMY_GOBLIN = '1', 
		ENEMY_ORC = '2',
		ENEMY_TROLL = '3', 
		ENEMY_SLIME = '4', 
		ENEMY_SKELETON = '5', 
		ENEMY_GHOST = '6', 
		GAVIN = 'G', 
		SHOP = '$', 
		WAYPOINT = '+' 
	};

	static Tile getTile(sf::Vector2ul);
	
	static Tile getTileAt(sf::Vector2f);

	static bool isOnGrid(sf::Vector2f);

	static size_t getWidth();

	static size_t getHeight();

	static sf::Vector2f getTilePosition(sf::Vector2ul);

	static std::vector<sf::Vector2ul> findTiles(Tile);

	static sf::Color getColor(Tile t);

	static void setColor(Tile t, sf::Color c);

	static void setOffset(const sf::Vector2f& _offset);

	static const sf::Vector2f& getOffset();

	static float getTileSize();
	
	

protected:
	static std::unique_ptr<Tile[]> _tiles;
	static size_t _width;
	static size_t _height;
	static sf::Vector2f _offset;

	static std::vector<std::unique_ptr<sf::RectangleShape>> _sprites;

	static void buildSprites(bool optimise = true);

	static float _tileSize;
	static std::map<Tile, sf::Color> _colours;
	
private:
	LevelSystem() = delete;

	~LevelSystem() = delete;
};