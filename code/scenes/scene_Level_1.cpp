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
Vector2f view_center;


void Level1Scene::Load() {

	ls::loadLevelFile("res/tilemaps/Level_1.txt", 240.f);

	TilePhysics();

	makeShops();

	makeTorches();

	makeGavin();

	makeCoin();

	makeChest();

	makeEnemies();

	

	player = makePlayer();
	view_center = player->getPosition();


	addUI();
	
	


	setLoaded(true);
}

void Level1Scene::UnLoad() {
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
	if (view_player_distance > 40.f)
		view_center += (player->getPosition() - view_center) *(float)dt * 3.5f;
	view.setCenter(view_center);

	Engine::GetWindow().setView(view);

	Scene::Update(dt);
}

void Level1Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}

