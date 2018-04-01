#include "scene_Settings_Graphics.h"
#include "../components/cmp_text.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_sprite.h"
#include "SFML\Graphics.hpp"
#include "../GameState.h"
#include "levelsystem.h"
#include "../components/cmp_btn.h"
#include "../code/Prefabs.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> btnBack;
static shared_ptr<Entity> btnDone;

static shared_ptr<Entity> btnLow;
static shared_ptr<Entity> btnMed;
static shared_ptr<Entity> btnHigh;
static shared_ptr<Entity> btn30;
static shared_ptr<Entity> btn60;
static shared_ptr<Entity> btnWindow;
static shared_ptr<Entity> btnFull;


void SettingsGraphicsScene::Load() 
{
	ls::loadLevelFile("res/backgrounds.txt", 240.f);

	{
		btnBack = makeButton("Back", Vector2f(150, 60));
		btnBack->setPosition(Vector2f(Engine::GetWindow().getSize().x / 7, 100.f));
	}

	{
		auto txtGraphics = makeEntity();
		auto t = txtGraphics->addComponent<TextComponent>("Graphics");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtGraphics->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 100.f));
	}

	{
		auto txtQuality = makeEntity();
		auto t = txtQuality->addComponent<TextComponent>("Quality");
		t->getText().setOrigin(0, t->getText().getGlobalBounds().height / 2);
		txtQuality->setPosition(Vector2f(Engine::GetWindow().getSize().x / 6, 250.f));

		btnLow = makeButton("Low", Vector2f(150, 60));
		btnLow->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 250.f));

		btnMed = makeButton("Medium", Vector2f(150, 60));
		btnMed->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 200, 250.f));

		btnHigh = makeButton("High", Vector2f(150, 60));
		btnHigh->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 400, 250.f));
	}

	{
		auto txtFPS = makeEntity();
		auto t = txtFPS->addComponent<TextComponent>("FPS");
		t->getText().setOrigin(0, t->getText().getGlobalBounds().height / 2);
		txtFPS->setPosition(Vector2f(Engine::GetWindow().getSize().x / 6, 350.f));

		btn30 = makeButton("30 FPS", Vector2f(150, 60));
		btn30->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 350.f));

		btn60 = makeButton("60 FPS", Vector2f(150, 60));
		btn60->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 200, 350.f));
	}


	{
		auto txtMode = makeEntity();
		auto t = txtMode->addComponent<TextComponent>("Video Mode");
		t->getText().setOrigin(0, t->getText().getGlobalBounds().height / 2);
		txtMode->setPosition(Vector2f(Engine::GetWindow().getSize().x / 6, 450.f));

		btnWindow = makeButton("Window", Vector2f(150, 60));
		btnWindow->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 450.f));

		btnFull = makeButton("Full", Vector2f(150, 60));
		btnFull->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 200, 450.f));

	}

	{
		btnDone = makeButton("Done", Vector2f(150, 60));
		btnDone->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 650.f));
	}
	setLoaded(true);
}

void SettingsGraphicsScene::UnLoad() 
{
	ls::unload();
	Scene::UnLoad();
}

void SettingsGraphicsScene::Update(const double& dt) 
{
	if (btnBack->get_components<BtnComponent>()[0]->isSelected())
	{
		Engine::ChangeScene((Scene*)&settings);
	}
	Scene::Update(dt);

	if (btnDone->get_components<BtnComponent>()[0]->isSelected())
	{
		Engine::ChangeScene((Scene*)&settings);
	}

	if (btnLow->get_components<BtnComponent>()[0]->isSelected())
	{
	}

	if (btnMed->get_components<BtnComponent>()[0]->isSelected())
	{
	}

	if (btnHigh->get_components<BtnComponent>()[0]->isSelected())
	{
	}

	if (btn60->get_components<BtnComponent>()[0]->isSelected())
	{
	}

	if (btn30->get_components<BtnComponent>()[0]->isSelected())
	{
	}

	if (btnWindow->get_components<BtnComponent>()[0]->isSelected())
	{
	}

	if (btnFull->get_components<BtnComponent>()[0]->isSelected())
	{
	}
}

void SettingsGraphicsScene::Render() 
{
	ls::render(Engine::GetWindow());
	Scene::Render();
}