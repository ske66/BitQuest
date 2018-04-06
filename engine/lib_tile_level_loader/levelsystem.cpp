#include "levelsystem.h"
#include <../src/system_resources.h>
#include <fstream>

using namespace std;
using namespace sf;

float LevelSystem::_tileSize(240.f);

//Create textures for all tiles and spawn points
std::map<LevelSystem::Tile, sf::IntRect> LevelSystem::_rectMap{
	{ WAYPOINT, IntRect(240,240, _tileSize, _tileSize) },
{ EMPTY, IntRect(240,240, _tileSize, _tileSize) },
{ START, IntRect(480,0, _tileSize, _tileSize) },
{ END, IntRect(240,240, _tileSize, _tileSize) },
{ WALL, IntRect(240, 0, _tileSize, _tileSize) },
{ FLOOR, IntRect(0,0, _tileSize, _tileSize) },
{ GROUND, IntRect(0,240, _tileSize, _tileSize) },
{ ROCKS, IntRect(480,240, _tileSize, _tileSize) },
{ ROCKS_SMALL, IntRect(720,240, _tileSize, _tileSize) },
{ BONES, IntRect(480,480, _tileSize, _tileSize) },
{ BONES_SMALL, IntRect(720,480, _tileSize, _tileSize) },
{ SHOP_SIGN_LEFT, IntRect(240,720, _tileSize, _tileSize) },
{ SHOP_SIGN_RIGHT, IntRect(0,720, _tileSize, _tileSize) },
{ GAVIN_SIGN_LEFT, IntRect(720,720, _tileSize, _tileSize) },
{ GAVIN_SIGN_RIGHT, IntRect(480,720, _tileSize, _tileSize) },
{ CHAINS, IntRect(720, 0, _tileSize, _tileSize) },
{ WINDOW, IntRect(240,480, _tileSize, _tileSize), },
{ ALCOVE, IntRect(0,480, _tileSize, _tileSize) },
{ TORCH, IntRect(240,240, _tileSize, _tileSize) },
{ CHEST, IntRect(240,240, _tileSize, _tileSize) },
{ COIN, IntRect(240,240, _tileSize, _tileSize) },
{ ENEMY_GOBLIN, IntRect(240,240, _tileSize, _tileSize) },
{ ENEMY_ORC, IntRect(720,240, _tileSize, _tileSize) },
{ ENEMY_TROLL, IntRect(480,480, _tileSize, _tileSize) },
{ ENEMY_SLIME, IntRect(720,480, _tileSize, _tileSize) },
{ ENEMY_SKELETON, IntRect(240,240, _tileSize, _tileSize) },
{ ENEMY_GHOST, IntRect(240,240, _tileSize, _tileSize) },
{ GAVIN, IntRect(240,240, _tileSize, _tileSize) },
{ SHOP, IntRect(240,240, _tileSize, _tileSize) } };

//get and set sprite to each tile
sf::IntRect LevelSystem::getSpriteRect(LevelSystem::Tile t)
{
	auto it = _rectMap.find(t);
	if (it == _rectMap.end())
	{
		return IntRect(12, 34, _tileSize, _tileSize);
	}
	return _rectMap[t];
}

void LevelSystem::setSpriteRect(LevelSystem::Tile t, sf::IntRect r)
{
	_rectMap[t] = r;
}

std::unique_ptr<LevelSystem::Tile[]> LevelSystem::_tiles;
size_t LevelSystem::_width;
size_t LevelSystem::_height;

Vector2f LevelSystem::_offset(0.f, 0.f);
Sprite LevelSystem::_map;

//Check to make sure the txt file can be parsed
void LevelSystem::loadLevelFile(const std::string &path, float tileSize) {

	_tileSize = tileSize;
	size_t w = 0, h = 0;
	string buffer;

	// Load in file to buffer
	ifstream f(path);
	if (f.good()) {
		f.seekg(0, std::ios::end);
		buffer.resize(f.tellg());
		f.seekg(0);
		f.read(&buffer[0], buffer.size());
		f.close();
	}
	else {
		throw string("Couldn't open level file: ") + path;
	}

	std::vector<Tile> temp_tiles;
	int widthCheck = 0;
	for (int i = 0; i < buffer.size(); ++i) {
		const char c = buffer[i];
		if (c == '\0') {
			break;
		}
		if (c == '\n') {
			if (w == 0) {
				w = i;
			}
			else if (w != (widthCheck - 1)) {
				throw string("non uniform width:" + to_string(h) + " ") + path;
			}
			widthCheck = 0;
			h++;
		}
		else {
			temp_tiles.push_back((Tile)c);
		}
		++widthCheck;
	}
	h++;
	if (temp_tiles.size() != (w * h)) {
		throw string("Can't parse level file") + path;
	}

	_tiles = std::make_unique<Tile[]>(w * h);
	_width = w;
	_height = h;
	std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
	buildSprites();
}

shared_ptr<Texture> tex;
RenderTexture bigMapTexture;

//Take all individual tiles and convert them into a MegaTexture
void LevelSystem::buildSprites() {

	struct tp {
		sf::Vector2f pos;
		sf::IntRect intRect;
	};
	vector<tp> tps;
	for (size_t y = 0; y < _height; ++y) {
		for (size_t x = 0; x < _width; ++x) {
			Tile t = getTile({ x, y });
			tps.push_back({ getTilePosition({ x,y }), getSpriteRect(t) });
		}
	}
	//read from Tileset
	tex = Resources::load<Texture>("NewTerrain.png");
	bigMapTexture.create(_tileSize * _width, _tileSize * _height);
	bigMapTexture.clear(Color::White);

	//Make everything a big sprite
	for (auto& t : tps)
	{
		auto s = Sprite();
		s.setTexture(*tex);
		s.setTextureRect(t.intRect);
		s.setPosition(t.pos);
		bigMapTexture.draw(s);

	}

	bigMapTexture.display();
	_map = Sprite(bigMapTexture.getTexture());
}
//draw Megatexture
void LevelSystem::render(RenderWindow& window)
{
	window.draw(_map);
}

LevelSystem::Tile LevelSystem::getTile(sf::Vector2ul p) {
	if (p.x > _width || p.y > _height)
	{
		return TILES::EMPTY;
	}
	return _tiles[(p.y * _width) + p.x];
}

size_t LevelSystem::getWidth() { return _width; }

size_t LevelSystem::getHeight() { return _height; }

sf::Vector2f LevelSystem::getTilePosition(sf::Vector2ul p)
{
	return (Vector2f(p.x, p.y) * _tileSize) + _offset;
}

std::vector<sf::Vector2ul> LevelSystem::findTiles(LevelSystem::Tile type)
{
	auto v = vector<sf::Vector2ul>();
	for (size_t i = 0; i < _width * _height; ++i)
	{
		if (_tiles[i] == type)
		{
			v.push_back({ i % _width, i / _width });
		}
	}
	return v;
}

LevelSystem::Tile LevelSystem::getTileAt(Vector2f v)
{
	auto a = v - _offset;
	if (a.x < 0 || a.y < 0)
	{
		throw string("tile out of range");
	}
	return getTile(Vector2ul((v - _offset) / (_tileSize)));
}

bool LevelSystem::isOnGrid(sf::Vector2f v)
{
	auto a = v - _offset;
	if (a.x < 0 || a.y < 0)
	{
		return false;
	}
	auto p = Vector2ul((v - _offset) / (_tileSize));
	if (p.x > _width || p.y > _height)
	{
		return false;
	}
	return true;
}

void LevelSystem::setOffset(const Vector2f& _offset)
{
	LevelSystem::_offset = _offset;
	buildSprites();
}

void LevelSystem::unload()
{
	_tiles.reset();
	_width = 0;
	_height = 0;
	_offset = { 0,0 };
}

const Vector2f& LevelSystem::getOffset() { return _offset; }

float LevelSystem::getTileSize() { return _tileSize; }