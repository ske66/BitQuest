#include "scene_LoadGame.h"
#include "../components/cmp_text.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_btn.h"
#include "SFML\Graphics.hpp"
#include "../GameState.h"
#include "engine.h"
#include "levelsystem.h"
#include "../code/Prefabs.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> btnBack;

void LoadGameScene::Load() 
{
	ls::loadLevelFile("res/tilemaps/Backgrounds.txt", 240.f);

	{
		auto txtLoadGame = makeEntity();
		auto t = txtLoadGame->addComponent<TextComponent>("Load Game");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtLoadGame->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 100.f));

		btnBack = makeButton("Back", Vector2f(150, 60));
		btnBack->setPosition(Vector2f(Engine::GetWindow().getSize().x / 7, 100.f));
	}

	setLoaded(true);
}

void LoadGameScene::UnLoad() {
	ls::unload();
	Scene::UnLoad();
}

void LoadGameScene::Update(const double& dt) 
{
	if (btnBack->get_components<BtnComponent>()[0]->isSelected())
	{
		Engine::ChangeScene((Scene*)&menu);
	}

	Scene::Update(dt);
}

void LoadGameScene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}