#include "scene_level1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_enemy_AI.h"
#include "../components/cmp_gavin_physics.h"
#include "../GameState.h"
#include <levelsystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static shared_ptr<Entity> gavin;

vector<shared_ptr<Entity>> goblins;
vector<shared_ptr<Entity>> orcs;
vector<shared_ptr<Entity>> trolls;
vector<shared_ptr<Entity>> slimes;
vector<shared_ptr<Entity>> skeletons;
vector<shared_ptr<Entity>> ghosts;

void Level1Scene::Load() {
	cout << "Scene 1 loading" << endl;
	
	ls::loadLevelFile("res/level_1.txt", 240.f);

	auto ho = Engine::getWindowSize().y - (ls::getHeight() * 240.f);
	ls::setOffset(Vector2f(0, ho));



	//PLAYER CREATION
	{
		player = makeEntity();
		player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
		auto s = player->addComponent<AnimationComponent>();
		s->Animation("Bob_spritesheet.png",Vector2f(0,150), Vector2u(8,8));
		player->addComponent<PlayerPhysicsComponent>(Vector2f(120, 240));
		
	}

	
	//GAVIN CREATION
	{

		gavin = makeEntity();
		gavin->setPosition(ls::getTilePosition(ls::findTiles(ls::GAVIN)[0]));
		auto s = gavin->addComponent<AnimationComponent>();
		s->Animation("Gavin_spritesheet.png", Vector2f(0, 150), Vector2u(8,8));
		gavin->addComponent<GavinPhysicsComponent>(Vector2f(120, 240));
		
	}

	/*
	//GOBLIN CREATION
	{
		auto goblin = makeEntity();
		goblin->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY_GOBLIN)[3]));

		sf::Texture temp_goblin;
		temp_goblin.loadFromFile("res\\textures\\Goblin_spritesheet.png");

		for (int i = 0; i < 4; ++i) {
			auto goblin = make_shared<Entity>();
			auto s = goblin->addComponent<TextureComponent>();
			s->setShape<sf::RectangleShape>(Vector2f(240.f, 240.f));
			s->setTexture(temp_goblin);
			s->getShape().setTexture(s->getTexture());
			s->getShape().setTextureRect(IntRect(0, 0, 240, 240));
			s->getShape().setOrigin(Vector2f(120.f, 120.f));

			goblin->addComponent<EnemyAIComponent>();
			//goblin->addComponent<EnemyPhysicsComponent>();

		}
	}


	//ORC CREATION

	{
		auto orc = makeEntity();
		orc->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY_ORC)[1]));

		sf::Texture temp_orc;
		temp_orc.loadFromFile("res\\textures\\Orc_spritesheet.png");

		for (int i = 0; i < 2; ++i) {
			auto orc = make_shared<Entity>();
			auto s = orc->addComponent<TextureComponent>();
			s->setShape<sf::RectangleShape>(Vector2f(240.f, 240.f));
			s->setTexture(temp_orc);
			s->getShape().setTexture(s->getTexture());
			s->getShape().setTextureRect(IntRect(0, 0, 240, 240));
			s->getShape().setOrigin(Vector2f(120.f, 120.f));

			orc->addComponent<EnemyAIComponent>();
			//orc->addComponent<EnemyPhysicsComponent>();

		}
	}

	
	//TROLL CREATION

	{
		auto troll = makeEntity();
		troll->setPosition(ls::getTilePosition(ls::findTiles(ls::ENEMY_TROLL)[0]));

		sf::Texture temp_troll;
		temp_troll.loadFromFile("res\\textures\\Troll_spritesheet.png");

		for (int i = 0; i < 1; ++i) {
			auto troll = make_shared<Entity>();
			auto s = troll->addComponent<TextureComponent>();
			s->setShape<sf::RectangleShape>(Vector2f(240.0f, 240.f));
			//s->setTexture(temp_)
		}

	}

	*/



	{

		auto floor = ls::findTiles(ls::FLOOR);
		for (auto f : floor)
		{
			auto pos = ls::getTilePosition(f);
			pos += Vector2f(120.f, 120.f);
			auto e = makeEntity();
			e->setPosition(pos);
			auto s = e->addComponent<SpriteComponent>();
			s->Sprite("NewTerrain.png", IntRect(0, 0, 240, 240));
			e->addComponent<PhysicsComponent>(false, Vector2f(240.f, 240.f));
		}
		
		auto walls = ls::findTiles(ls::WALL);
		for (auto w : walls) 
		{
			auto pos = ls::getTilePosition(w);
			pos += Vector2f(120.f, 120.f);
			auto e = makeEntity();
			e->setPosition(pos);
			auto s = e->addComponent<SpriteComponent>();
			s->Sprite("NewTerrain.png", IntRect(240, 240,240 , 240));
			e->addComponent<PhysicsComponent>(false, Vector2f(240.f,240.f));
		}
		
	}



//	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	//cout << "Scene 1 Loaded" << endl;

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

	sf::View player_veiw(sf::FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
	player_veiw.setCenter(player->getPosition());
	Engine::GetWindow().setView(player_veiw);
	Scene::Update(dt);
}

void Level1Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}