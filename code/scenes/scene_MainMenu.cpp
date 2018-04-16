#include "scene_MainMenu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_btn.h"
#include "../GameState.h"
#include "../code/Prefabs.h"
#include "../code/SaveLoad.h"
#include "system_resources.h"
#include "engine.h"
#include "levelsystem.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;
using namespace sf;


void MainMenuScene::Load()
{
	double mark = sqrt(16);

	cout << mark << endl;

	ls::loadLevelFile("res/tilemaps/Backgrounds.txt", 240.f);

	//Music
	_musicMenu = Resources::get<Music>("Menu_Music.wav");
	_musicMenu->play();
	_musicMenu->setLoop(true);
	_musicMenu->setVolume(musicVolume);


		//Position the game's Logo
		auto Logo = makeEntity();
		auto log = Logo->addComponent<SpriteComponent>();
		log->Sprite("Logo.png", IntRect(0, 0, 640, 320));
		log->getSprite().setOrigin(log->getSprite().getLocalBounds().width/2, log->getSprite().getLocalBounds().height/2);

		Logo->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, Engine::GetWindow().getSize().y * 0.25));
	
	
		_btns.clear();

		_btnNewGame.reset();
		_btnNewGame = makeButton("New Game", Vector2f(230, 60));
		_btnNewGame->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5, Engine::GetWindow().getSize().y / 2 * 1.5));
		_btns.push_back(_btnNewGame);
		
		auto sword = makeEntity();
		auto sw = sword->addComponent<SpriteComponent>();
		sw->Sprite("Sword.png", IntRect(0, 0, 60, 60));
		sw->getSprite().setOrigin(sw->getSprite().getLocalBounds().width/ 2, sw->getSprite().getLocalBounds().height/2);
		sword->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5, Engine::GetWindow().getSize().y / 2 * 1.3));
		


		_btnLoadGame.reset();
		_btnLoadGame = makeButton("Load Game", Vector2f(230, 60));
		_btnLoadGame->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5 * 2, Engine::GetWindow().getSize().y / 2 * 1.5));
		_btns.push_back(_btnLoadGame);

		auto shield = makeEntity();
		auto sh = shield->addComponent<SpriteComponent>();
		sh->Sprite("Shield.png", IntRect(0, 0, 60, 60));
		sh->getSprite().setOrigin(sh->getSprite().getLocalBounds().width / 2, sh->getSprite().getLocalBounds().height / 2);
		shield->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5 * 2, Engine::GetWindow().getSize().y / 2 * 1.3));


	
		_btnSettings.reset();
		_btnSettings = makeButton("Settings", Vector2f(230, 60));
		_btnSettings->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5 * 3, Engine::GetWindow().getSize().y / 2 * 1.5));
		_btns.push_back(_btnSettings);

		auto chest = makeEntity();
		auto ch = chest->addComponent<SpriteComponent>();
		ch->Sprite("Chest.png", IntRect(0, 0, 60, 60));
		ch->getSprite().setOrigin(ch->getSprite().getLocalBounds().width / 2, ch->getSprite().getLocalBounds().height / 2);
		chest->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5 * 3, Engine::GetWindow().getSize().y / 2 * 1.3));
	
		

		_btnExit.reset();
		_btnExit = makeButton("Quit Game", Vector2f(230, 60));
		_btnExit->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5 * 4, Engine::GetWindow().getSize().y / 2 * 1.5));
		_btns.push_back(_btnExit);

		auto door = makeEntity();
		auto d = door->addComponent<SpriteComponent>();
		d->Sprite("Door.png", IntRect(0, 0, 60, 60));
		d->getSprite().setOrigin(d->getSprite().getLocalBounds().width / 2, d->getSprite().getLocalBounds().height / 2);
		door->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5 * 4, Engine::GetWindow().getSize().y / 2 * 1.3));
	


	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

	setLoaded(true);
}


void MainMenuScene::UnLoad() {
	_musicMenu->stop();
	_musicMenu.reset();
	
	ls::unload();
	Scene::UnLoad();
}


void MainMenuScene::Update(const double& dt) 
{

		if (_btnNewGame->get_components<BtnComponent>()[0]->isSelected())
		{
			SaveLoad::ResetGame();
			Engine::ChangeScene((Scene*)&level1);

		}

		if (_btnLoadGame->get_components<BtnComponent>()[0]->isSelected())
		{
			SaveLoad::LoadGame();
			Engine::ChangeScene((Scene*)&level1);

		}

		if (_btnSettings->get_components<BtnComponent>()[0]->isSelected())
		{
			Engine::ChangeScene((Scene*)&settings);
		}

		if (_btnExit->get_components<BtnComponent>()[0]->isSelected())
		{
			SaveLoad::ResetGame();
			Engine::GetWindow().close();
		}

	Scene::Update(dt);
}


void MainMenuScene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}