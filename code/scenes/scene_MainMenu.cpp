#include "scene_MainMenu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_btn.h"
#include "../GameState.h"
#include "../code/Prefabs.h"
#include "engine.h"
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

static shared_ptr<Entity> btnNewGame;
static shared_ptr<Entity> btnLoadGame;
static shared_ptr<Entity> btnSettings;
static shared_ptr<Entity> btnExit;


void MainMenuScene::Load() 
{
	{
		auto background = makeEntity();
		auto s = background->addComponent<SpriteComponent>();
		background->setPosition(Vector2f(0, 0));
		s->Sprite("Background.png", IntRect(0, 0, 6500, 6500));
	}

	{
		//Position the game's Logo
		auto Logo = makeEntity();
		auto log = Logo->addComponent<SpriteComponent>();
		log->Sprite("Logo.png", IntRect(0, 0, 640, 320));
		log->getSprite().setOrigin(log->getSprite().getLocalBounds().width/2, log->getSprite().getLocalBounds().height/2);

		Logo->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, Engine::GetWindow().getSize().y * 0.25));
	
	}
	
	{

		btnNewGame = makeButton("New Game", Vector2f(250, 60));
		btnNewGame->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5, Engine::GetWindow().getSize().y / 2 * 1.5));
		
		auto sword = makeEntity();
		auto s = sword->addComponent<SpriteComponent>();
		s->Sprite("Sword.png", IntRect(0, 0, 60, 60));
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width/ 2, s->getSprite().getLocalBounds().height/2);

		sword->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5, Engine::GetWindow().getSize().y / 2 * 1.3));
		
	}
	
	{

		btnLoadGame = makeButton("Load Game", Vector2f(250, 60));
		btnLoadGame->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5 * 2, Engine::GetWindow().getSize().y / 2 * 1.5));
	
		auto shield = makeEntity();
		auto s = shield->addComponent<SpriteComponent>();
		s->Sprite("Shield.png", IntRect(0, 0, 60, 60));
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

		shield->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5 * 2, Engine::GetWindow().getSize().y / 2 * 1.3));

	}

	{
		btnSettings = makeButton("Settings", Vector2f(250, 60));
		btnSettings->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5 * 3, Engine::GetWindow().getSize().y / 2 * 1.5));

		auto chest = makeEntity();
		auto s = chest->addComponent<SpriteComponent>();
		s->Sprite("Chest.png", IntRect(0, 0, 60, 60));
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

		chest->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5 * 3, Engine::GetWindow().getSize().y / 2 * 1.3));
	}

	{
		
		btnExit = makeButton("Quit Game", Vector2f(250, 60));
		btnExit->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5 * 4, Engine::GetWindow().getSize().y / 2 * 1.5));

		auto door = makeEntity();
		auto s = door->addComponent<SpriteComponent>();
		s->Sprite("Door.png", IntRect(0, 0, 60, 60));
		s->getSprite().setOrigin(s->getSprite().getLocalBounds().width / 2, s->getSprite().getLocalBounds().height / 2);

		door->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5 * 4, Engine::GetWindow().getSize().y / 2 * 1.3));
	}

	setLoaded(true);
}

void MainMenuScene::Update(const double& dt) 

{

	auto e = Engine::getEvent();

		sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::GetWindow());
		sf::Vector2f worldPos = Engine::GetWindow().mapPixelToCoords(pixelPos);



		if (btnNewGame->get_components<BtnComponent>()[0]->isSelected())
		{
			Engine::ChangeScene((Scene*)&level1);
		}

		if (btnLoadGame->get_components<BtnComponent>()[0]->isSelected())
		{
			Engine::ChangeScene((Scene*)&loadgame);
		}

		if (btnSettings->get_components<BtnComponent>()[0]->isSelected())
		{
			Engine::ChangeScene((Scene*)&settings);
		}

		if (btnExit->get_components<BtnComponent>()[0]->isSelected())
		{
			Engine::GetWindow().close();
		}

	Scene::Update(dt);
}