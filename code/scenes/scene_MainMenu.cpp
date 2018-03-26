#include "scene_MainMenu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../GameState.h"
#include "engine.h"
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

static shared_ptr<Entity> btnStart;

void MainMenuScene::Load() {
	cout << "Main Menu Load \n";

	sf::Vector2i position = sf::Mouse::getPosition();

	
	{
		
		auto background = makeEntity();
		auto s = background->addComponent<SpriteComponent>();
		background->setPosition(Vector2f(0, 0));
		s->Sprite("Background.png", IntRect(0, 0, 6500, 6500));
		
	}

	{

		//Position the game's Logo
		auto Logo = makeEntity();
		auto s = Logo->addComponent<SpriteComponent>();

		Logo->setPosition(Vector2f(Engine::GetWindow().getSize().x / 3, 100.f));
		s->Sprite("Logo.png", IntRect(0, 0, 640, 320));

	}
	
	{
		auto btn = makeEntity();
		auto sword = makeEntity();
		auto txtNewGame = makeEntity();

		auto b = btn->addComponent<SpriteComponent>();
		auto s = sword->addComponent<SpriteComponent>();
		auto t = txtNewGame->addComponent<TextComponent>("New Game");
		//FINISH COMPONENTS
		s->Sprite("Sword.png", IntRect(0, 0, 60, 60));
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getLocalBounds().height / 2);

		sword->setPosition(Vector2f(370.f, 540.f));
		txtNewGame->setPosition(Vector2f(280.f, 500.f));
	}
	
	{
		auto shield = makeEntity();
		auto txtLoadGame = makeEntity();

		auto s = shield->addComponent<SpriteComponent>();
		auto t = txtLoadGame->addComponent<TextComponent>("Load Game");

		s->Sprite("Shield.png", IntRect(0, 0, 60, 60));
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getLocalBounds().height / 2);

		shield->setPosition(Vector2f(610.f, 540.f));
		txtLoadGame->setPosition(Vector2f(520.f, 500.f));
	}

	{
		auto chest = makeEntity();
		auto txtSettings = makeEntity();
		
		auto c = chest->addComponent<SpriteComponent>();
		auto t = txtSettings->addComponent<TextComponent>("Settings");

		c->Sprite("chest.png", IntRect(0, 0, 60, 60));
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getLocalBounds().height / 2);
		
		chest->setPosition(Vector2f(850.f, 540.f));
		txtSettings->setPosition(Vector2f(760.f, 500.f));
	}

	{
		auto door = makeEntity();
		auto txtQuitGame = makeEntity();

		auto d = door->addComponent<SpriteComponent>();
		auto t = txtQuitGame->addComponent<TextComponent>("End Game");

		d->Sprite("door.png", IntRect(0, 0, 60, 60));
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getLocalBounds().height / 2);

		door->setPosition(Vector2f(1090.f, 540.f));
		txtQuitGame->setPosition(Vector2f(1000.f, 500.f));
	
	}


	setLoaded(true);


}

void MainMenuScene::Update(const double& dt) 

{/*
	{
		sf::RectangleShape newGameRect;
		newGameRect.setSize(Vector2f(100, 200));
		newGameRect.setPosition(Vector2f(520.f, 500.f));
		newGameRect.setFillColor(Color::Red);


		if (newGameRect.getGlobalBounds().contains(Engine::GetWindow().mapPixelToCoords(sf::Mouse::getPosition())) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
		{
			Engine::ChangeScene(&level1);
		}
	}
	*/
	Scene::Update(dt);
}