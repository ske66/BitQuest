#include "scene_level_1.h"
#include "../GameState.h"
#include "../code/Prefabs.h"
#include <levelsystem.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
Vector2f view_center;

void Level1Scene::Load() {

	ls::loadLevelFile("res/Tilemaps/TestEnvironment.txt", 240.f);  //the test environment is designed to push the game to it's limit

	player = makePlayer();
	view_center = player->getPosition();

	TilePhysics();

	makeTorches();

	makeShops();

	makeGavin();

	makeCoins();

	makeChests();

	makeEnemies();

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


	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		Vector2f currentPos = player->getPosition();

		int posX = currentPos.x;
		int posY = currentPos.y;

		Vector2f saveCoords = Vector2f(((posX + 240 / 2) / 240) * 240, ((posY + 240) / 240) * 240);

		Vector2u saveTile = Vector2u(saveCoords.x / 240, saveCoords.y / 240);
		cout << saveTile << endl;

		std::ifstream inFile("res/Tilemaps/testEnvironment.txt");

		std::ofstream outFile("res/Tilemaps/testEnvironment(save1).txt");

		string s = "s";

		outFile << inFile.rdbuf();

		Engine::ChangeScene(&menu);
	}
	Scene::Update(dt);

}

void Level1Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}

