#include "scene_Settings.h"
#include "SFML\Graphics.hpp"
#include "../GameState.h"

using namespace std;
using namespace sf;

void SettingsScene::Load() {

	setLoaded(true);
}

void SettingsScene::UnLoad() {
	cout << "Settings Unload" << endl;
	Scene::UnLoad();
}

void SettingsScene::Update(const double& dt) {

	Scene::Update(dt);
}

void SettingsScene::Render() {
	
	Scene::Render();
}
