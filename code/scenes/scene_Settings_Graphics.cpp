#include "scene_Settings_Graphics.h"
#include "SFML\Graphics.hpp"
#include "../GameState.h"

using namespace std;
using namespace sf;

void SettingsGraphicsScene::Load() {

	setLoaded(true);
}

void SettingsGraphicsScene::UnLoad() {
	cout << "Graphics Settings Unload" << endl;
	Scene::UnLoad();
}

void SettingsGraphicsScene::Update(const double& dt) {

	Scene::Update(dt);
}

void SettingsGraphicsScene::Render() {

	Scene::Render();
}