#include "scene_Settings_Gameplay.h"
#include "SFML\Graphics.hpp"
#include "../GameState.h"

using namespace std;
using namespace sf;

void SettingsGameplayScene::Load() {

	setLoaded(true);
}

void SettingsGameplayScene::UnLoad() {
	cout << "Gameplay Settings Unload" << endl;
	Scene::UnLoad();
}

void SettingsGameplayScene::Update(const double& dt) {

	Scene::Update(dt);
}

void SettingsGameplayScene::Render() {

	Scene::Render();
}