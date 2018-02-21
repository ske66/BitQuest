#include "Game.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"

using namespace std;
using namespace sf;

void MenuScene::update(float dt) {
	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		activeScene = gameScene;
	}
	Scene::update(dt);
	text.setString("Almost Pacman");
}

void MenuScene::render() {
	Scene::render();
}

void MenuScene::load() {
	Font font;
	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
	text.setString("Bitquest!");
}

void GameScene::update(float dt) {
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);
}

void GameScene::render() {
	Scene::render();
}

void GameScene::respawn() {}

void GameScene::load() {

	//Player spawning
	shared_ptr<Entity> player = make_shared<Player>();
	_ents.list.push_back(player);
	player->setPosition({ gameWidth * 0.5, gameHeight * 0.75 });

	shared_ptr<Entity>enemy = make_shared<Enemy>();
	_ents.list.push_back(enemy);
	enemy->setPosition({ gameWidth * 0.8, gameHeight * 0.75 });

}