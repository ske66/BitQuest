#include "scene_Settings_Graphics.h"
#include "../components/cmp_text.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_sprite.h"
#include "SFML\Graphics.hpp"
#include "../GameState.h"
#include "levelsystem.h"
#include "../components/cmp_btn.h"
#include "../code/Prefabs.h"
#include "engine.h"
#include <fstream>

using namespace std;
using namespace sf;



void SettingsGraphicsScene::Load()
{
	ls::loadLevelFile("res/tilemaps/backgrounds.txt", 240.f);

	_btns.clear();

	{
		_btnBack.reset();
		_btnBack = makeButton("Back", Vector2f(150, 60));
		_btnBack->setPosition(Vector2f(Engine::GetWindow().getSize().x / 7, 100.f));
		_btns.push_back(_btnBack);
	}

	{
		auto txtGraphics = makeEntity();
		auto t = txtGraphics->addComponent<TextComponent>("Graphics");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtGraphics->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 100.f));
	}

	{
		auto txtResolution = makeEntity();
		auto t = txtResolution->addComponent<TextComponent>("Resolution");
		t->getText().setOrigin(0, t->getText().getGlobalBounds().height / 2);
		txtResolution->setPosition(Vector2f(Engine::GetWindow().getSize().x / 6, 250.f));

		_ResLow.reset();
		_ResLow = makeButton("1280x720", Vector2f(150, 60));
		_ResLow->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 250.f));
		_btns.push_back(_ResLow);

		_ResMed.reset();
		_ResMed = makeButton("1600x900", Vector2f(150, 60));
		_ResMed->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 230, 250.f));
		_btns.push_back(_ResMed);

		_ResHigh.reset();
		_ResHigh = makeButton("1920x1080", Vector2f(150, 60));
		_ResHigh->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 460, 250.f));
		_btns.push_back(_ResHigh);
	}

	{
		auto txtFPS = makeEntity();
		auto t = txtFPS->addComponent<TextComponent>("FPS");
		t->getText().setOrigin(0, t->getText().getGlobalBounds().height / 2);
		txtFPS->setPosition(Vector2f(Engine::GetWindow().getSize().x / 6, 350.f));

		_btn30.reset();
		_btn30 = makeButton("30 FPS", Vector2f(150, 60));
		_btn30->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 350.f));
		_btns.push_back(_btn30);

		_btn60.reset();
		_btn60 = makeButton("60 FPS", Vector2f(150, 60));
		_btn60->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 230, 350.f));
		_btns.push_back(_btn60);
	}


	{
		auto txtMode = makeEntity();
		auto t = txtMode->addComponent<TextComponent>("Vysnc");
		t->getText().setOrigin(0, t->getText().getGlobalBounds().height / 2);
		txtMode->setPosition(Vector2f(Engine::GetWindow().getSize().x / 6, 450.f));

		_btnOn.reset();
		_btnOn = makeButton("Fullscreen", Vector2f(150, 60));
		_btnOn->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 450.f));
		_btns.push_back(_btnOn);

		_btnOff.reset();
		_btnOff = makeButton("Windowed", Vector2f(150, 60));
		_btnOff->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 230, 450.f));
		_btns.push_back(_btnOff);

	}

	{
		_btnDone.reset();
		_btnDone = makeButton("Done", Vector2f(150, 60));
		_btnDone->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 650.f));
		_btns.push_back(_btnDone);
	}

	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

	setLoaded(true);
}

void SettingsGraphicsScene::UnLoad()
{
	ls::unload();
	Scene::UnLoad();
}

void SettingsGraphicsScene::Update(const double& dt)
{
	if (_btnBack->get_components<BtnComponent>()[0]->isSelected())
	{
		Engine::ChangeScene((Scene*)&settings);
	}

	if (_btnDone->get_components<BtnComponent>()[0]->isSelected())
	{
		Engine::GetWindow().close();

		Engine::Start(game_width, game_heigth, "Bitquest!", &menu, frameRate);
	}



	if (_clickCooldown >= 0.0f)_clickCooldown -= dt;

	if (_clickCooldown < 0.0f)
	{

		if (_ResLow->get_components<BtnComponent>()[0]->isSelected())
		{
			game_width = 1280;
			game_heigth = 720;
		}

		if (_ResMed->get_components<BtnComponent>()[0]->isSelected())
		{
			game_width = 1600;				
			game_heigth = 900;
		}

		if (_ResHigh->get_components<BtnComponent>()[0]->isSelected())
		{	
			game_width = 1920;			
			game_heigth = 1080;
		}
		
			if (_btn60->get_components<BtnComponent>()[0]->isSelected())
			{
				frameRate = 60;
			}

			if (_btn30->get_components<BtnComponent>()[0]->isSelected())
			{
				frameRate = 30;
			}

			if (_btnOn->get_components<BtnComponent>()[0]->isSelected())
			{
				//windowMode = "Fullscreen";
			}

			if (_btnOff->get_components<BtnComponent>()[0]->isSelected())
			{
				//windowMode = "Windowed";
			}
		}

	Scene::Update(dt);
}

void SettingsGraphicsScene::Render()
{
	ls::render(Engine::GetWindow());
	Scene::Render();
}