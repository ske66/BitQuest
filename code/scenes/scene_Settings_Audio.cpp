#include "scene_Settings_Audio.h"
#include "SFML\Graphics.hpp"
#include "../GameState.h"

using namespace std;
using namespace sf;

void SettingsAudioScene::Load() {

	setLoaded(true);
}

void SettingsAudioScene::UnLoad() {
	cout << "Audio Settings Unload" << endl;
	Scene::UnLoad();
}

void SettingsAudioScene::Update(const double& dt) {

	Scene::Update(dt);
}

void SettingsAudioScene::Render() {

	Scene::Render();
}