#include "scene_Settings_Graphics.h"
#include "../components/cmp_text.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_sprite.h"
#include "SFML\Graphics.hpp"
#include "../GameState.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> btnGraphicsBack;

static shared_ptr<Entity> txtLow;
static shared_ptr<Entity> txtMed;
static shared_ptr<Entity> txtHigh;
static shared_ptr<Entity> txt30;
static shared_ptr<Entity> txt60;
static shared_ptr<Entity> txtWindow;
static shared_ptr<Entity> txtFull;

double totalTimeGraphics = 0.0f;
double clickDelayGraphics = 0.2f;


void SettingsGraphicsScene::Load() 
{
	{

		btnGraphicsBack = makeEntity();
		auto b = btnGraphicsBack->addComponent<ShapeComponent>();
		b->setShape<sf::RectangleShape>(Vector2f(100.f, 60.f));
		b->getShape().setOrigin(b->getShape().getGlobalBounds().width / 2, b->getShape().getGlobalBounds().height / 2);
		btnGraphicsBack->setPosition(Vector2f(200.f, 100.f));
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
		auto t = txtSettings->addComponent<TextComponent>("Graphics");
		t->getText().setOrigin(t->getText().getGlobalBounds().width, t->getText().getGlobalBounds().height / 2);
		txtSettings->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 100.f));
	}

	{
		auto txtQuality = makeEntity();
		auto t = txtQuality->addComponent<TextComponent>("Quality");
		t->getText().setOrigin(0, t->getText().getGlobalBounds().height / 2);
		txtQuality->setPosition(Vector2f(Engine::GetWindow().getSize().x / 6, 250.f));

	    txtLow = makeEntity();
		auto tl = txtLow->addComponent<TextComponent>("Low");
		tl->getText().setOrigin(0, tl->getText().getGlobalBounds().height / 2);
		tl->getText().setCharacterSize(18);
		txtLow->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 250.f));

		txtMed = makeEntity();
		auto tm = txtMed->addComponent<TextComponent>("Medium");
		tm->getText().setOrigin(0, tm->getText().getGlobalBounds().height / 2);
		tm->getText().setCharacterSize(18);
		txtMed->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 200, 250.f));

		txtHigh = makeEntity();
		auto th = txtHigh->addComponent<TextComponent>("High");
		th->getText().setOrigin(0, tl->getText().getGlobalBounds().height / 2);
		th->getText().setCharacterSize(18);
		th->getText().setFillColor(Color(240, 178, 0));
		txtHigh->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 400, 250.f));
	}

	{
		auto txtFPS = makeEntity();
		auto t = txtFPS->addComponent<TextComponent>("FPS");
		t->getText().setOrigin(0, t->getText().getGlobalBounds().height / 2);
		txtFPS->setPosition(Vector2f(Engine::GetWindow().getSize().x / 6, 400.f));
		
		txt30 = makeEntity();
		auto t30 = txt30->addComponent<TextComponent>("30fps");
		t30->getText().setOrigin(0, t30->getText().getGlobalBounds().height / 2);
		t30->getText().setCharacterSize(18);
		txt30->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 400.f));

		txt60 = makeEntity();
		auto t60 = txt60->addComponent<TextComponent>("60fps");
		t60->getText().setOrigin(0, t60->getText().getGlobalBounds().height / 2);
		t60->getText().setCharacterSize(18);
		t60->getText().setFillColor(Color(240, 178, 0));
		txt60->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 200, 400.f));
	}

	{
		auto txtMode = makeEntity();
		auto t = txtMode->addComponent<TextComponent>("Video Mode");
		t->getText().setOrigin(0, t->getText().getGlobalBounds().height / 2);
		txtMode->setPosition(Vector2f(Engine::GetWindow().getSize().x / 6, 550.f));

		txtWindow = makeEntity();
		auto tw = txtWindow->addComponent<TextComponent>("Windowed");
		tw->getText().setOrigin(0, tw->getText().getGlobalBounds().height / 2);
		tw->getText().setCharacterSize(18);
		tw->getText().setFillColor(Color(240, 178, 0));
		txtWindow->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 550.f));

		txtFull = makeEntity();
		auto tf = txtFull->addComponent<TextComponent>("Full Screen");
		tf->getText().setOrigin(0, tf->getText().getGlobalBounds().height / 2);
		tf->getText().setCharacterSize(18);
		txtFull->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 200, 550.f));

	}

	setLoaded(true);
}

void SettingsGraphicsScene::UnLoad() {
	cout << "Graphics Settings Unload" << endl;
	Scene::UnLoad();
}

void SettingsGraphicsScene::Update(const double& dt) 
{
	auto e = Engine::getEvent();

	totalTimeGraphics += dt;


	sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::GetWindow());
	sf::Vector2f worldPos = Engine::GetWindow().mapPixelToCoords(pixelPos);

	if (totalTimeGraphics >= clickDelayGraphics)
	{
		totalTimeGraphics -= clickDelayGraphics;
	
		if (btnGraphicsBack->GetCompatibleComponent<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(worldPos))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				Engine::ChangeScene((Scene*)&settings);
			}
		}

	}

		if (txtLow->GetCompatibleComponent<TextComponent>()[0]->getText().getGlobalBounds().contains(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			txtLow->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(240, 178, 0));
			txtMed->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(255,255,255));
			txtHigh->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(255,255,255));
		}

		if (txtMed->GetCompatibleComponent<TextComponent>()[0]->getText().getGlobalBounds().contains(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			txtLow->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(255, 255, 255));
			txtMed->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(240, 178, 0));
			txtHigh->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(255, 255, 255));
		}

		if (txtHigh->GetCompatibleComponent<TextComponent>()[0]->getText().getGlobalBounds().contains(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			txtLow->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(255, 255, 255));
			txtMed->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(255, 255, 255));
			txtHigh->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(240, 178, 0));
		}




		if (txt30->GetCompatibleComponent<TextComponent>()[0]->getText().getGlobalBounds().contains(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			txt30->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(240, 178, 0));
			txt60->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(255, 255, 255));
		}

		if (txt60->GetCompatibleComponent<TextComponent>()[0]->getText().getGlobalBounds().contains(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			txt30->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(255, 255, 255));
			txt60->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(240, 178, 0));
		}



		if (txtWindow->GetCompatibleComponent<TextComponent>()[0]->getText().getGlobalBounds().contains(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			txtWindow->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(240, 178, 0));
			txtFull->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(255,255,255));
		}

		if (txtFull->GetCompatibleComponent<TextComponent>()[0]->getText().getGlobalBounds().contains(worldPos) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			txtWindow->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(255, 255, 255));
			txtFull->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(240, 178, 0));
		}

	Scene::Update(dt);
}

void SettingsGraphicsScene::Render() {

	Scene::Render();
}