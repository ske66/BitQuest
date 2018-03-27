#include "scene_level_1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_enemy_AI.h"
#include "../components/cmp_player_status.h"
#include "../components/cmp_gavin_physics.h"
#include "../components/cmp_enemy_AI.h"
#include "../GameState.h"
#include <levelsystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static shared_ptr<Entity> gavin;


void Level1Scene::Load() {
	cout << "Scene 1 loading" << endl;
	
	ls::loadLevelFile("res/level_1.txt", 240.f);

	auto ho = Engine::getWindowSize().y - (ls::getHeight() * 240.f);
	ls::setOffset(Vector2f(0, ho));


	//TILEMAP GENERATION

	{

		{
			//background texture to hide spawns
			auto background = makeEntity();
			background->setPosition(Vector2f(200, -6000));
			auto s = background->addComponent<SpriteComponent>();
			//s->
			s->Sprite("Background.png", IntRect(0, 0, 6500, 6500));
		}

		//Floor textures
		auto floor = ls::findTiles(ls::FLOOR);
		for (auto f : floor)
		{
			auto pos = ls::getTilePosition(f);
			pos += Vector2f(120.f, 120.f);
			auto e = makeEntity();
			e->setPosition(pos);
			auto s = e->addComponent<SpriteComponent>();
			s->Sprite("NewTerrain.png", IntRect(0, 0, 240, 240));
			e->addComponent<PhysicsComponent>(false, Vector2f(480, 240));
		}
		
		//Ground (under floor) textures
		auto ground = ls::findTiles(ls::GROUND);
		for (auto g : ground)
		{
			auto pos = ls::getTilePosition(g);
			pos += Vector2f(120.f, 120.f);
			auto e = makeEntity();
			e->setPosition(pos);
			auto s = e->addComponent<SpriteComponent>();
			s->Sprite("NewTerrain.png", IntRect(0, 240, 240, 240));
		}

		
		//Wall Textures
		auto walls = ls::findTiles(ls::WALL);
		for (auto w : walls)
		{
			auto pos = ls::getTilePosition(w);
			pos += Vector2f(120, 120);
			auto e = makeEntity();
			e->setPosition(pos);
			auto s = e->addComponent<SpriteComponent>();
			s->Sprite("NewTerrain.png", IntRect(240, 0, 240, 240));
			e->addComponent<PhysicsComponent>(false, Vector2f(120, 240));
		}

	}

	//COIN CREATION
	auto coins = ls::findTiles(ls::COIN);
	for (auto c :coins)
	{
		auto pos = ls::getTilePosition(c);
		pos += Vector2f(120.f, 120.f);
		auto e = makeEntity();
		e->setPosition(pos);
		auto s = e->addComponent<AnimationComponent>();
		s->Animation("Coin_spritesheet.png", Vector2f(0, -60), IntRect(0, 0, 60, 60), Vector2u(6, 1));
	}


	//PLAYER CREATION
	{
		player = makeEntity();
		player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
		auto s = player->addComponent<AnimationComponent>();
		s->Animation("Bob_spritesheet.png",Vector2f(0,120), IntRect(0,0,240,240), Vector2u(8,8));
		player->addComponent<PlayerPhysicsComponent>(Vector2f(120, 240));
		player->addComponent<PlayerStatusComponent>();
		player->addTag("player"); 
	}

	
	//GAVIN CREATION
	{

		gavin = makeEntity();
		gavin->setPosition(ls::getTilePosition(ls::findTiles(ls::GAVIN)[0]));
		auto s = gavin->addComponent<AnimationComponent>();
		s->Animation("Gavin_spritesheet.png", Vector2f(0, 120), IntRect(0, 0, 240, 240), Vector2u(8,8));
		gavin->addComponent<GavinPhysicsComponent>(Vector2f(0, 240));
		gavin->addComponent<GavinAiComponent>();
		gavin->addTag("gavin");
		
	}

	
	//GOBLIN CREATION
	{

	auto goblins = ls::findTiles(ls::ENEMY_GOBLIN);
	for (auto go : goblins)
		{
			auto pos = ls::getTilePosition(go);
			pos += Vector2f(120.f, 120.f);
			auto goblin = makeEntity();
			goblin->setPosition(pos);
			auto s = goblin->addComponent<AnimationComponent>();
			s->Animation("Goblin_spritesheet.png", Vector2f(0, 120), IntRect(0, 0, 240, 240), Vector2u(8, 8));
			goblin->addComponent<GavinPhysicsComponent>(Vector2f(0, 240));
		}
	}
	 

	//ORC CREATION

	{

	auto orcs = ls::findTiles(ls::ENEMY_ORC);
	for (auto o : orcs)
		{
			auto pos = ls::getTilePosition(o);
			pos += Vector2f(120.f, 120.f);
			auto orc = makeEntity();
			orc->setPosition(pos);
			auto s = orc->addComponent<AnimationComponent>();
			s->Animation("Orc_spritesheet.png", Vector2f(0, 120), IntRect(0, 0, 240, 240), Vector2u(8, 8));
			orc->addComponent<GavinPhysicsComponent>(Vector2f(0, 240));
		}
	}

	
	//TROLL CREATION

	{

	auto trolls = ls::findTiles(ls::ENEMY_TROLL);
	for (auto tr : trolls)
		{
			auto pos = ls::getTilePosition(tr);
			pos += Vector2f(120.f, 120.f);
			auto troll = makeEntity();
			troll->setPosition(pos);
			auto s = troll->addComponent<AnimationComponent>();
			s->Animation("Troll_spritesheet.png", Vector2f(0, 120), IntRect(0, 0, 240, 240), Vector2u(8, 8));
			troll->addComponent<GavinPhysicsComponent>(Vector2f(0, 240));
		}
	}

	setLoaded(true);
}

void Level1Scene::UnLoad() {
	cout << "Scene 1 Unload" << endl;
	player.reset();
	ls::unload();
	Scene::UnLoad();
}

void Level1Scene::Update(const double& dt) {

	if (ls::getTileAt(player->getPosition()) == ls::END) {
		Engine::ChangeScene((Scene*)&menu);
	}

	sf::View player_view(sf::FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
	player_view.setCenter(player->getPosition());
	Engine::GetWindow().setView(player_view);
	Scene::Update(dt);
}

void Level1Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}

