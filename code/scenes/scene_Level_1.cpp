#include "scene_level_1.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_gavin_AI.h"
#include "../components/cmp_gavin_physics.h"
#include "../components/cmp_player_controller.h"
#include "../components/cmp_general_AI.h"
#include "../GameState.h"
#include "../code/Prefabs.h"
#include <levelsystem.h>
#include <iostream>
#include <thread>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static shared_ptr<Entity> gavin;
Vector2f view_center;


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

	//PLAYER CREATION
	{
		player = makePlayer();
		view_center = player->getPosition();

		gavin = makeGavin();

		makeEnemies();

		makeCoin();
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


	View view(FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
	float view_player_distance = sqrt(((player->getPosition().x - view_center.x) * (player->getPosition().x - view_center.x)) + ((player->getPosition().y - view_center.y) * (player->getPosition().y - view_center.y)));
	if (view_player_distance > 80.f)
		view_center += (player->getPosition() - view_center) *(float)dt * 2.3f;
	view.setCenter(view_center);

	Engine::GetWindow().setView(view);

	Scene::Update(dt);
}

void Level1Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}

