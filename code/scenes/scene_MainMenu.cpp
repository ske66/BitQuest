#include "scene_MainMenu.h"
#include "../components/cmp_text.h"
#include "../GameState.h"
#include <SFML\Window\Keyboard.hpp>
#include <iostream>

using namespace std;
using namespace sf;

void MainMenuScene::Load() {
	cout << "Main Menu Load \n";
	{
		auto txt = makeEntity();
		auto t = txt->addComponent<TextComponent>("BITQUEST!\nPress Space to Start!");
	}
	setLoaded(true);
}

void MainMenuScene::Update(const double& dt) {

	if (sf::Keyboard::isKeyPressed(Keyboard::Space))
	{
		Engine::ChangeScene(&level1);
	}

	Scene::Update(dt);
}