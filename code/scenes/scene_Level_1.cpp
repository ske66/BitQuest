#include "scene_level_1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_gavin_AI.h"
#include "../components/cmp_gavin_physics.h"
#include "../components/cmp_player_controller.h"
#include "../components/cmp_general_AI.h"
#include "../GameState.h"
#include <levelsystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static shared_ptr<Entity> gavin;
static shared_ptr<Entity> BlackBar;
static shared_ptr<Entity> BlackBarBottom;

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
			e->addComponent<PhysicsComponent>(false, Vector2f(230, 240));
			s->getSprite().setOrigin(s->getSprite().getGlobalBounds().width / 2, s->getSprite().getGlobalBounds().height / 2);



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
			s->getSprite().setOrigin(s->getSprite().getGlobalBounds().width / 2, s->getSprite().getGlobalBounds().height / 2);
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
			s->getSprite().setOrigin(s->getSprite().getGlobalBounds().width / 2, s->getSprite().getGlobalBounds().height / 2);
		}

	}


	//COIN CREATION
	auto coins = ls::findTiles(ls::COIN);
	for (auto c : coins)
	{
		auto pos = ls::getTilePosition(c);
		pos += Vector2f(120.f, 120.f);
		auto e = makeEntity();
		e->setPosition(pos);

		e->addComponent<StateComponent>();
		auto s = e->addComponent<AnimationComponent>();
		s->Animation("Coin_spritesheet.png", Vector2f(0, -60), IntRect(0, 0, 60, 60), Vector2u(6, 1));
		e->addComponent<PhysicsComponent>(false, Vector2f(30, 15));
		s->getSprite().setOrigin(s->getSprite().getGlobalBounds().width / 2, s->getSprite().getGlobalBounds().height / 2);
		e->addTag("coin");
	}



	//PLAYER CREATION
	{
		player = makeEntity();
		player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
		player->addComponent<StateComponent>();
		player->addComponent<PlayerControlerComponent>();
		auto s = player->addComponent<AnimationComponent>();
		s->Animation("Bob_spritesheet.png", Vector2f(0, 120), IntRect(0, 0, 240, 240), Vector2u(8, 8));
		player->addComponent<PlayerPhysicsComponent>(Vector2f(120, 220));
		s->getSprite().setOrigin(s->getSprite().getGlobalBounds().width / 2, s->getSprite().getGlobalBounds().height / 2);
		player->addTag("player");
	}


	//GAVIN CREATION
	{

		gavin = makeEntity();
		gavin->setPosition(ls::getTilePosition(ls::findTiles(ls::GAVIN)[0]));
		gavin->addComponent<StateComponent>();
		gavin->addComponent<GavinPhysicsComponent>(Vector2f(120, 240));
		gavin->addComponent<GavinAiComponent>();
		auto s = gavin->addComponent<AnimationComponent>();
		s->Animation("Gavin_spritesheet.png", Vector2f(0, 120), IntRect(0, 0, 240, 240), Vector2u(8, 8));
		s->getSprite().setOrigin(s->getSprite().getGlobalBounds().width / 2, s->getSprite().getGlobalBounds().height / 2);
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
			goblin->addComponent<StateComponent>();
			auto s = goblin->addComponent<AnimationComponent>();
			s->Animation("Goblin_spritesheet.png", Vector2f(120, 230), IntRect(0, 0, 240, 240), Vector2u(8, 8));
			auto f = goblin->addComponent<PhysicsComponent>(true , Vector2f(100,200));
			goblin->addComponent<GeneralAiComponent>();
			s->getSprite().setOrigin(s->getSprite().getGlobalBounds().width / 2, s->getSprite().getGlobalBounds().height / 2);
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
			//orc->addComponent<StateComponent>();
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
			troll->addComponent<StateComponent>();
			auto s = troll->addComponent<AnimationComponent>();
			s->Animation("Troll_spritesheet.png", Vector2f(0, 120), IntRect(0, 0, 240, 240), Vector2u(8, 8));
			troll->addComponent<GavinPhysicsComponent>(Vector2f(0, 240));
		}


		//Load UI
		{
			BlackBar = makeEntity();
			auto bar = BlackBar->addComponent<ShapeComponent>();
			bar->setShape<sf::RectangleShape>(Vector2f(1300, 50.f));
			bar->getShape().setOrigin(0, 50);
			bar->getShape().setFillColor(Color::Black);

			BlackBarBottom = makeEntity();
			auto bar2 = BlackBarBottom->addComponent<ShapeComponent>();
			bar2->setShape<sf::RectangleShape>(Vector2f(1300, 50.f));
			bar2->getShape().setOrigin(0, 50);
			bar2->getShape().setFillColor(Color::Black);
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

	BlackBar->setPosition({ Engine::GetWindow().getView().getCenter().x,
						   Engine::GetWindow().getView().getCenter().y });

	BlackBarBottom->setPosition({ Engine::GetWindow().getView().getCenter().x,
							Engine::GetWindow().getView().getCenter().y });


	BlackBar->setPosition(Vector2f(BlackBar->getPosition().x - 640, BlackBar->getPosition().y - Engine::GetWindow().getSize().y / 2 + 50));
	BlackBarBottom->setPosition(Vector2f(BlackBarBottom->getPosition().x - 640, BlackBarBottom->getPosition().y - Engine::GetWindow().getSize().y / 2 + 720));


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

