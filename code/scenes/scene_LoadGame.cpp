#include "scene_LoadGame.h"
#include "../components/cmp_text.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_sprite.h"
#include "SFML\Graphics.hpp"
#include "../GameState.h"
#include "engine.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> btnLoadGameBack;


void LoadGameScene::Load() {

	cout << "Load Game Loaded \n";

	{
		btnLoadGameBack = makeEntity();
		auto b = btnLoadGameBack->addComponent<ShapeComponent>();
		b->setShape<sf::RectangleShape>(Vector2f(100.f, 60.f));
		b->getShape().setOrigin(b->getShape().getGlobalBounds().width / 2, b->getShape().getGlobalBounds().height / 2);
		btnLoadGameBack->setPosition(Vector2f(200.f, 100.f));
	}

	auto background = makeEntity();
	auto s = background->addComponent<SpriteComponent>();
	background->setPosition(Vector2f(0, 0));
	s->Sprite("Background.png", IntRect(0, 0, 6500, 6500));

	{
		auto arrow = makeEntity();
		auto s = arrow->addComponent<SpriteComponent>();
		s->Sprite("arrow.png", IntRect(0, 0, 80, 50));
		s->getSprite().setOrigin(s->getSprite().getGlobalBounds().width / 2, s->getSprite().getGlobalBounds().height / 2);
		arrow->setPosition(Vector2f(200.f, 100.f));
	}

	{
		auto txtLoadGame = makeEntity();
		auto t = txtLoadGame->addComponent<TextComponent>("Load Game");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtLoadGame->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 100.f));
	}


	setLoaded(true);
}

void LoadGameScene::UnLoad() {
	cout << "Load Game Unload" << endl;
	Scene::UnLoad();
}

void LoadGameScene::Update(const double& dt) 
{

	sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::GetWindow());
	sf::Vector2f worldPos = Engine::GetWindow().mapPixelToCoords(pixelPos);


	if (btnLoadGameBack->GetCompatibleComponent<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(worldPos))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			Engine::ChangeScene((Scene*)&menu);
		}
	}

	Scene::Update(dt);
}

void LoadGameScene::Render() {

	Scene::Render();
}