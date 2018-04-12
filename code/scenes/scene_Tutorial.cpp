#include "scene_Tutorial.h"
#include "../GameState.h"
#include "../code/Prefabs.h"
#include "engine.h"
#include "levelsystem.h"
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

void TutorialScene::Load()
{

	ls::loadLevelFile("res/Tilemaps/tutorial_level.txt", 240.f);

	TilePhysics();

	makeTorches();

	makeGavin();

	makeCoins();

	makeEnemies();

	_player = makePlayer(ls::getTilePosition(ls::findTiles(ls::START)[0]));

	_view_center = _player->getPosition();

	addUI();

	setLoaded(true);
}


void TutorialScene::UnLoad() {
	ls::unload();
	Scene::UnLoad();
}


void TutorialScene::Update(const double& dt)
{
	if (ls::getTileAt(_player->getPosition()) == ls::END) {
		Engine::ChangeScene((Scene*)&level1);
	}

	View view(FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
	float view_player_distance = sqrt(((_player->getPosition().x - _view_center.x) * (_player->getPosition().x - _view_center.x)) + ((_player->getPosition().y - _view_center.y) * (_player->getPosition().y - _view_center.y)));
	if (view_player_distance > 40.f)
		_view_center += (_player->getPosition() - _view_center) *(float)dt * 3.5f;
	view.setCenter(_view_center);

	Engine::GetWindow().setView(view);

	Scene::Update(dt);
}

void TutorialScene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}