#include "scene_MainMenu.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_animation.h"
#include "../GameState.h"
#include "engine.h"
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

static shared_ptr<Entity> highlightStart;
static shared_ptr<Entity> highlightLoad;
static shared_ptr<Entity> highlightSettings;
static shared_ptr<Entity> highlightExit;
static shared_ptr<Entity> btnStartGame;
static shared_ptr<Entity> btnLoadGame;
static shared_ptr<Entity> btnSettings;
static shared_ptr<Entity> btnExit;

void MainMenuScene::Load() 
{

	//Button Locations
	{
		btnStartGame = makeEntity();
		auto bs = btnStartGame->addComponent<ShapeComponent>();
		bs->setShape<sf::RectangleShape>(Vector2f(200.f, 115.f));
		bs->getShape().setOrigin(bs->getShape().getGlobalBounds().width / 2, bs->getShape().getGlobalBounds().height / 2);
		btnStartGame->setPosition(Vector2f(Engine::GetWindow().getSize().x / 4 - 40.f, 470.f));

		btnLoadGame = makeEntity();
		auto bl = btnLoadGame->addComponent<ShapeComponent>();
		bl->setShape<sf::RectangleShape>(Vector2f(200.f, 115.f));
		bl->getShape().setOrigin(bl->getShape().getGlobalBounds().width / 2, bl->getShape().getGlobalBounds().height / 2);
		btnLoadGame->setPosition(Vector2f(Engine::GetWindow().getSize().x / 4 + 200.f, 470.f));

		btnSettings = makeEntity();
		auto bse = btnSettings->addComponent<ShapeComponent>();
		bse->setShape<sf::RectangleShape>(Vector2f(200.f, 115.f));
		bse->getShape().setOrigin(bse->getShape().getGlobalBounds().width / 2, bse->getShape().getGlobalBounds().height / 2);
		btnSettings->setPosition(Vector2f(Engine::GetWindow().getSize().x / 4 + 440.f, 470.f));

		btnExit = makeEntity();
		auto be = btnExit->addComponent<ShapeComponent>();
		be->setShape<sf::RectangleShape>(Vector2f(200.f, 115.f));
		be->getShape().setOrigin(be->getShape().getGlobalBounds().width / 2, be->getShape().getGlobalBounds().height / 2);
		btnExit->setPosition(Vector2f(Engine::GetWindow().getSize().x / 4 + 680.f, 470.f));
	}
	
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
		
		auto txtNewGame = makeEntity();
		auto t = txtNewGame->addComponent<TextComponent>("New Game");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtNewGame->setPosition(Vector2f(280.f, 500.f));


		auto sword = makeEntity();
		auto s = sword->addComponent<SpriteComponent>();
		s->Sprite("Sword.png", IntRect(0, 0, 60, 60));
		sword->setPosition(Vector2f(370.f, 540.f));


		highlightStart = makeEntity();
		auto h = highlightStart->addComponent<ShapeComponent>();
		h->setShape<sf::RectangleShape>(Vector2f(200.f, 5.f));
		h->getShape().setFillColor(Color(128, 128, 128));
		h->getShape().setOrigin(h->getShape().getGlobalBounds().width / 2, h->getShape().getGlobalBounds().height / 2);
		highlightStart->setPosition(Vector2f(Engine::GetWindow().getSize().x / 4 - 40.f, 525.f));

	}
	
	{

		

		auto shield = makeEntity();
		auto s = shield->addComponent<SpriteComponent>();
		s->Sprite("Shield.png", IntRect(0, 0, 60, 60));
		shield->setPosition(Vector2f(610.f, 540.f));

		auto txtLoadGame = makeEntity();
		auto t = txtLoadGame->addComponent<TextComponent>("Load Game");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getLocalBounds().height / 2);
		txtLoadGame->setPosition(Vector2f(520.f, 500.f));


		highlightLoad = makeEntity();
		auto h = highlightLoad->addComponent<ShapeComponent>();
		h->setShape<sf::RectangleShape>(Vector2f(200.f, 5.f));
		h->getShape().setFillColor(Color(128, 128, 128));
		h->getShape().setOrigin(h->getShape().getGlobalBounds().width / 2, h->getShape().getGlobalBounds().height / 2);
		highlightLoad->setPosition(Vector2f(Engine::GetWindow().getSize().x / 4 + 200.f, 525.f));
	}

	{
		
		auto chest = makeEntity();
		auto c = chest->addComponent<SpriteComponent>();
		c->Sprite("chest.png", IntRect(0, 0, 60, 60));
		chest->setPosition(Vector2f(850.f, 540.f));

		auto txtSettings = makeEntity();
		auto t = txtSettings->addComponent<TextComponent>("Settings");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getLocalBounds().height / 2);
		txtSettings->setPosition(Vector2f(760.f, 500.f));

		highlightSettings = makeEntity();
		auto h = highlightSettings->addComponent<ShapeComponent>();
		h->setShape<sf::RectangleShape>(Vector2f(200.f, 5.f));
		h->getShape().setFillColor(Color(128, 128, 128));
		h->getShape().setOrigin(h->getShape().getGlobalBounds().width / 2, h->getShape().getGlobalBounds().height / 2);
		highlightSettings->setPosition(Vector2f(Engine::GetWindow().getSize().x / 4 + 440.f, 525.f));



	}

	{
		
		auto door = makeEntity();
		auto d = door->addComponent<SpriteComponent>();
		d->Sprite("door.png", IntRect(0, 0, 60, 60));
		door->setPosition(Vector2f(1090.f, 540.f));

		auto txtQuitGame = makeEntity();
		auto t = txtQuitGame->addComponent<TextComponent>("End Game");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtQuitGame->setPosition(Vector2f(1000.f, 500.f));

		highlightExit = makeEntity();
		auto h = highlightExit->addComponent<ShapeComponent>();
		h->setShape<sf::RectangleShape>(Vector2f(200.f, 5.f));
		h->getShape().setFillColor(Color(128, 128, 128));
		h->getShape().setOrigin(h->getShape().getGlobalBounds().width / 2, h->getShape().getGlobalBounds().height / 2);
		highlightExit->setPosition(Vector2f(Engine::GetWindow().getSize().x / 4 + 680.f, 525.f));

	}

	setLoaded(true);
}

void MainMenuScene::Update(const double& dt) 

{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::GetWindow());
		sf::Vector2f worldPos = Engine::GetWindow().mapPixelToCoords(pixelPos);


		if (btnStartGame->GetCompatibleComponent<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(worldPos))
		{
			highlightStart->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(240, 178, 0));

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				Engine::ChangeScene((Scene*)&level1);
			}
		}
		else
		{
			highlightStart->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(128,128,128));
		}
		

		if (btnLoadGame->GetCompatibleComponent<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(worldPos))
		{
			highlightLoad->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(240, 178, 0));

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				Engine::ChangeScene((Scene*)&loadgame);
			}
		}
		else
		{
			highlightLoad->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(128, 128, 128));
		}


		if (btnSettings->GetCompatibleComponent<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(worldPos))
		{
			highlightSettings->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(240, 178, 0));

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				Engine::ChangeScene((Scene*)&settings);
			}
		}
		else
		{
			highlightSettings->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(128, 128, 128));
		}




		if (btnExit->GetCompatibleComponent<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(worldPos))
		{
			highlightExit->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(240, 178, 0));

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//Engine::GetWindow().close;
			}
		}
		else
		{
			highlightExit->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(128, 128, 128));
		}
		
	

	Scene::Update(dt);
}