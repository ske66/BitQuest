#include "scene_Settings.h"
#include "../components/cmp_text.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_sprite.h"
#include "SFML\Graphics.hpp"
#include "../GameState.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> btnBack;
static shared_ptr<Entity> btnGraphics;
static shared_ptr<Entity> btnAudio;
static shared_ptr<Entity> btnGameplay;

static shared_ptr<Entity> highlightGraphics;
static shared_ptr<Entity> highlightAudio;
static shared_ptr<Entity> highlightGameplay;

double totalTime = 0.0f;
double clickDelay = 0.2f;


void SettingsScene::Load() 
{
	{
		btnBack = makeEntity();
		auto b = btnBack->addComponent<ShapeComponent>();
		b->setShape<sf::RectangleShape>(Vector2f(100.f, 60.f));
		b->getShape().setOrigin(b->getShape().getGlobalBounds().width / 2, b->getShape().getGlobalBounds().height / 2);
		btnBack->setPosition(Vector2f(200.f, 100.f));

		btnGraphics = makeEntity();
		auto g = btnGraphics->addComponent<ShapeComponent>();
		g->setShape<sf::RectangleShape>(Vector2f(400.f, 60.f));
		g->getShape().setOrigin(g->getShape().getGlobalBounds().width / 2, g->getShape().getGlobalBounds().height / 2);
		btnGraphics->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 300.f));

		btnAudio = makeEntity();
		auto a = btnAudio->addComponent<ShapeComponent>();
		a->setShape<sf::RectangleShape>(Vector2f(300.f, 60.f));
		a->getShape().setOrigin(a->getShape().getGlobalBounds().width / 2, a->getShape().getGlobalBounds().height / 2);
		btnAudio->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 420.f));

		btnGameplay = makeEntity();
		auto gp = btnGameplay->addComponent<ShapeComponent>();
		gp->setShape<sf::RectangleShape>(Vector2f(400.f, 60.f));
		gp->getShape().setOrigin(gp->getShape().getGlobalBounds().width / 2, gp->getShape().getGlobalBounds().height / 2);
		btnGameplay->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 540.f));

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
		auto txtSettings = makeEntity();
		auto t = txtSettings->addComponent<TextComponent>("Settings");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtSettings->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 100.f));
	}

	{
		auto txtGraphics = makeEntity();
		auto t = txtGraphics->addComponent<TextComponent>("Graphics Settings");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtGraphics->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 300.f));

		highlightGraphics = makeEntity();
		auto h = highlightGraphics->addComponent<ShapeComponent>();
		h->setShape<sf::RectangleShape>(Vector2f(400.f, 5.f));
		h->getShape().setFillColor(Color(128, 128, 128));
		h->getShape().setOrigin(h->getShape().getGlobalBounds().width / 2, h->getShape().getGlobalBounds().height / 2);
		highlightGraphics->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 330.f));
	}

	{
		auto txtAudio = makeEntity();
		auto t = txtAudio->addComponent<TextComponent>("Audio Settings");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtAudio->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 420.f));

		highlightAudio = makeEntity();
		auto h = highlightAudio->addComponent<ShapeComponent>();
		h->setShape<sf::RectangleShape>(Vector2f(300.f, 5.f));
		h->getShape().setFillColor(Color(128, 128, 128));
		h->getShape().setOrigin(h->getShape().getGlobalBounds().width / 2, h->getShape().getGlobalBounds().height / 2);
		highlightAudio->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 450.f));
	}

	{
		auto txtGameplay = makeEntity();
		auto t = txtGameplay->addComponent<TextComponent>("Gameplay Settings");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtGameplay->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 540.f));

		highlightGameplay = makeEntity();
		auto h = highlightGameplay->addComponent<ShapeComponent>();
		h->setShape<sf::RectangleShape>(Vector2f(400.f, 5.f));
		h->getShape().setFillColor(Color(128, 128, 128));
		h->getShape().setOrigin(h->getShape().getGlobalBounds().width / 2, h->getShape().getGlobalBounds().height / 2);
		highlightGameplay->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 570.f));
	}



	setLoaded(true);
}

void SettingsScene::UnLoad() {
	cout << "Settings Unload" << endl;
	Scene::UnLoad();
}

void SettingsScene::Update(const double& dt) 
{
	auto e = Engine::getEvent();

	totalTime += dt;


	sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::GetWindow());
	sf::Vector2f worldPos = Engine::GetWindow().mapPixelToCoords(pixelPos);

	if (totalTime >= clickDelay)
	{
		totalTime -= clickDelay;

		if (btnGraphics->GetCompatibleComponent<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(worldPos))
		{
			highlightGraphics->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(240, 178, 0));

			if (e.mouseButton.button == sf::Mouse::Left)
			{
				Engine::ChangeScene((Scene*)&settingsGraphics);	
			}	
		}
		else
		{
			highlightGraphics->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(128, 128, 128));
		}
		



		if (btnAudio->GetCompatibleComponent<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(worldPos))
		{
			highlightAudio->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(240, 178, 0));

			if (e.mouseButton.button == sf::Mouse::Left)
			{
				Engine::ChangeScene((Scene*)&settingsAudio);
			}
		}
		else
		{
			highlightAudio->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(128, 128, 128));
		}
			



		if (btnGameplay->GetCompatibleComponent<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(worldPos))
		{
			highlightGameplay->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(240, 178, 0));

			if (e.mouseButton.button == sf::Mouse::Left)
			{
				Engine::ChangeScene((Scene*)&settingsGameplay);
			}
		}
		else
		{
			highlightGameplay->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(128, 128, 128));
		}



		if (btnBack->GetCompatibleComponent<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(worldPos))
		{
			if (e.mouseButton.button == sf::Mouse::Left)
			{
				Engine::ChangeScene((Scene*)&menu);
			}
		}
	}

	Scene::Update(dt);
}

void SettingsScene::Render() {
	
	Scene::Render();
}
