#include "scene_LoadGame.h"
#include "SFML\Graphics.hpp"
#include "../GameState.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_text.h"

using namespace std;
using namespace sf;

void LoadGameScene::Load() {

	cout << "Load Game Loaded \n";

	{

		auto background = makeEntity();
		auto s = background->addComponent<SpriteComponent>();
		background->setPosition(Vector2f(0, 0));
		s->Sprite("Background.png", IntRect(0, 0, 6500, 6500));

	}

	{
		auto txtLoadGame = makeEntity();
		auto t = txtLoadGame->addComponent<TextComponent>("Load Game");

		//t->getText().setOrigin(t->getText().getGlobalBounds().width / 3, 100.f);
		t->getText().setCharacterSize(32);

		txtLoadGame->setPosition(Vector2f(Engine::GetWindow().getSize().x / 3, 100.f));
	}


	setLoaded(true);
}

void LoadGameScene::UnLoad() {
	cout << "Load Game Unload" << endl;
	Scene::UnLoad();
}

void LoadGameScene::Update(const double& dt) {

	Scene::Update(dt);
}

void LoadGameScene::Render() {

	Scene::Render();
}