#include "scene_level_1.h"
#include "../GameState.h"
#include "../code/Prefabs.h"
#include "../code/components/cmp_btn.h"
#include <levelsystem.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace sf;

static shared_ptr<Entity> player;
static shared_ptr<Entity> Save;
static shared_ptr<Entity> Quit;
static shared_ptr<Entity> Resume;
Vector2f view_center;


void Level1Scene::Load() {

	ls::loadLevelFile("res/Tilemaps/TestEnvironment.txt", 240.f);  //the test environment is designed to push the game to it's limit

	int loadPosX;
	int loadPosY;

	ifstream InFile("res/SaveStates/TestLevelSave.txt");
	(InFile >> loadPosX >> loadPosY);

	cout << loadPosX << endl;

	cout << loadPosY << endl;


	if (loadGame == true)
	{
		player = makePlayer(Vector2f(loadPosX,loadPosY-240));
	}
	else
	{
		player = makePlayer(Vector2f(1200, 15360));
	}

	view_center = player->getPosition();

	TilePhysics();

	makeTorches();

	makeShops();

	makeGavin();

	makeCoins();

	makeChests();

	makeEnemies();

	addUI();


	_music_level1 = Resources::get<Music>("Level_Music.wav");
	_music_level1->play();
	_music_level1->setLoop(true);


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


	if (Keyboard::isKeyPressed(Keyboard::H))
	{

		//Started Save Game/Load Game
		
		Vector2f currentPos = player->getPosition();

		int posX = currentPos.x;
		int posY = currentPos.y;

		Vector2u saveCoords = Vector2u(((posX + 240 / 2) / 240) * 240, ((posY + 240) / 240) * 240);

		cout << saveCoords << endl;

		std::ofstream outFile("res/SaveStates/TestLevelSave.txt");
		outFile << saveCoords.x << endl;
		outFile << saveCoords.y << endl;
		outFile.close();
		//Position Saved
		
		Engine::ChangeScene(&menu);
		
	}
	Scene::Update(dt);

}

void Level1Scene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}

