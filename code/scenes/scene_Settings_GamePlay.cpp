#include "scene_Settings_Gameplay.h"
#include "../components/cmp_text.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_sprite.h"
#include "SFML\Graphics.hpp"
#include "../GameState.h"
#include "engine.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> btnGamePlayBack;

void SettingsGameplayScene::Load() 
{


	{
		btnGamePlayBack = makeEntity();
		auto b = btnGamePlayBack->addComponent<ShapeComponent>();
		b->setShape<sf::RectangleShape>(Vector2f(100.f, 60.f));
		b->getShape().setOrigin(b->getShape().getGlobalBounds().width / 2, b->getShape().getGlobalBounds().height / 2);
		btnGamePlayBack->setPosition(Vector2f(200.f, 100.f));
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
		auto txtGameplay = makeEntity();
		auto t = txtGameplay->addComponent<TextComponent>("Gameplay");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtGameplay->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 100.f));
	}

	{
		auto txtWalkLeft = makeEntity();
		auto wl = txtWalkLeft->addComponent<TextComponent>("Left");
		wl->getText().setOrigin(wl->getText().getGlobalBounds().width / 2, wl->getText().getGlobalBounds().height / 2);
		txtWalkLeft->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 - 450, 300.f));
		
		auto txtWalkRight = makeEntity();
		auto wr = txtWalkRight->addComponent<TextComponent>("Right");
		wr->getText().setOrigin(wr->getText().getGlobalBounds().width / 2, wr->getText().getGlobalBounds().height / 2);
		txtWalkRight->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 - 250, 300.f));

		auto txtJump = makeEntity();
		auto j = txtJump->addComponent<TextComponent>("Jump");
		j->getText().setOrigin(j->getText().getGlobalBounds().width / 2, j->getText().getGlobalBounds().height / 2);
		txtJump->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 - 50, 300.f));

		auto txtAttack = makeEntity();
		auto a = txtAttack->addComponent<TextComponent>("Attack");
		a->getText().setOrigin(a->getText().getGlobalBounds().width / 2, a->getText().getGlobalBounds().height / 2);
		txtAttack->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 150, 300.f));
		
		auto txtSwitch = makeEntity();
		auto s= txtSwitch->addComponent<TextComponent>("Switch");
		s->getText().setOrigin(s->getText().getGlobalBounds().width / 2, s->getText().getGlobalBounds().height / 2);
		txtSwitch->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 350, 300.f));

		//Event event;

	}
	setLoaded(true);
}

void SettingsGameplayScene::UnLoad() {
	cout << "Gameplay Settings Unload" << endl;
	Scene::UnLoad();
}

void SettingsGameplayScene::Update(const double& dt) 
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::GetWindow());
	sf::Vector2f worldPos = Engine::GetWindow().mapPixelToCoords(pixelPos);

	
		if (btnGamePlayBack->GetCompatibleComponent<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(worldPos))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				Engine::ChangeScene((Scene*)&settings);
			}
		}

	Scene::Update(dt);
}

void SettingsGameplayScene::Render() 
{


	Scene::Render();
}