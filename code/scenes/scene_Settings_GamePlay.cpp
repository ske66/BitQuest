#include "scene_Settings_Gameplay.h"
#include "../components/cmp_text.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_sprite.h"
#include "SFML\Graphics.hpp"
#include "SFML\Window\Event.hpp"
#include "../GameState.h"
#include "../code/Prefabs.h"
#include"../components/cmp_btn.h"
#include "levelsystem.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace sf;

static shared_ptr<Entity> btnBack;
static shared_ptr<Entity> btnDone;
static shared_ptr<Entity> walkLeftBox;
static shared_ptr<Entity> walkRightBox;
static shared_ptr<Entity> jumpBox;
static shared_ptr<Entity> attackBox;
static shared_ptr<Entity> switchBox;

static shared_ptr<Entity> LeftChar;
static shared_ptr<Entity> RightChar;
static shared_ptr<Entity> JumpChar;
static shared_ptr<Entity> AttackChar;
static shared_ptr<Entity> SwitchChar;

//READ IN FROM FILE

string txtwalkLeft = "A";
string txtwalkRight = "D";
string txtjump = "W"; 
string txtattack = "_";
string txtswitch = "Q";

void SettingsGameplayScene::Load() 
{
	ifstream file("res/savestates/PlayerControls.txt");
	while (file >> txtwalkLeft >> txtwalkRight >> txtjump >> txtattack >> txtswitch)
	{
	}

	ls::loadLevelFile("res/tilemaps/Backgrounds.txt", 240.f);

	{
		btnBack = makeButton("Back", Vector2f(150, 60));
		btnBack->setPosition(Vector2f(Engine::GetWindow().getSize().x / 7, 100.f));
	}


	{
		auto Gameplay = makeEntity();
		auto t = Gameplay->addComponent<TextComponent>("Gameplay");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		Gameplay->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 100.f));
	}

	{
		//Set walk left

		auto WalkLeft = makeEntity();
		auto wl = WalkLeft->addComponent<TextComponent>("Left");
		wl->getText().setOrigin(wl->getText().getGlobalBounds().width / 2, wl->getText().getGlobalBounds().height / 2);
		WalkLeft->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 - 400, 300.f));

		walkLeftBox = makeEntity();
		auto wlb = walkLeftBox->addComponent<ShapeComponent>();
		wlb->setShape<sf::RectangleShape>(Vector2f(40.f, 50.f));
		wlb->getShape().setOrigin(wlb->getShape().getGlobalBounds().width / 2, wlb->getShape().getGlobalBounds().height / 2);
		walkLeftBox->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 - 400, 380.f));

		LeftChar = makeEntity();
		auto lc = LeftChar->addComponent<TextComponent>(txtwalkLeft);
		lc->getText().setOrigin(lc->getText().getGlobalBounds().width / 2, lc->getText().getGlobalBounds().height / 2);
		LeftChar->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 - 400, 380.f));

	}
	
	
	{
		//Set walk right

		auto WalkRight = makeEntity();
		auto wr = WalkRight->addComponent<TextComponent>("Right");
		wr->getText().setOrigin(wr->getText().getGlobalBounds().width / 2, wr->getText().getGlobalBounds().height / 2);
		WalkRight->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 - 200, 300.f));
		
		walkRightBox = makeEntity();
		auto wrb = walkRightBox->addComponent<ShapeComponent>();
		wrb->setShape<sf::RectangleShape>(Vector2f(40.f, 50.f));
		wrb->getShape().setOrigin(wrb->getShape().getGlobalBounds().width / 2, wrb->getShape().getGlobalBounds().height / 2);
		walkRightBox->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 - 200, 380.f));

		RightChar = makeEntity();
		auto rc = RightChar->addComponent<TextComponent>(txtwalkRight);
		rc->getText().setOrigin(rc->getText().getGlobalBounds().width / 2, rc->getText().getGlobalBounds().height / 2);
		RightChar->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 - 200, 380.f));
	}

	{
		//Set jump

		auto Jump = makeEntity();
		auto j = Jump->addComponent<TextComponent>("Jump");
		j->getText().setOrigin(j->getText().getGlobalBounds().width / 2, j->getText().getGlobalBounds().height / 2);
		Jump->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 300.f));

		jumpBox = makeEntity();
		auto jb = jumpBox->addComponent<ShapeComponent>();
		jb->setShape<sf::RectangleShape>(Vector2f(40.f, 50.f));
		jb->getShape().setOrigin(jb->getShape().getGlobalBounds().width / 2, jb->getShape().getGlobalBounds().height / 2);
		jumpBox->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 380.f));

		JumpChar = makeEntity();
		auto jc = JumpChar->addComponent<TextComponent>(txtjump);
		jc->getText().setOrigin(jc->getText().getGlobalBounds().width / 2, jc->getText().getGlobalBounds().height / 2);
		JumpChar->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 380.f));
	}

	{
		//Set attack

		auto Attack = makeEntity();
		auto a = Attack->addComponent<TextComponent>("Attack");
		a->getText().setOrigin(a->getText().getGlobalBounds().width / 2, a->getText().getGlobalBounds().height / 2);
		Attack->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 200, 300.f));

	    attackBox = makeEntity();
		auto ab = attackBox->addComponent<ShapeComponent>();
		ab->setShape<sf::RectangleShape>(Vector2f(40.f, 50.f));
		ab->getShape().setOrigin(ab->getShape().getGlobalBounds().width / 2, ab->getShape().getGlobalBounds().height / 2);
		attackBox->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 200, 380.f));

		AttackChar = makeEntity();
		auto ac = AttackChar->addComponent<TextComponent>(txtattack);
		ac->getText().setOrigin(ac->getText().getGlobalBounds().width / 2, ac->getText().getGlobalBounds().height / 2);
		AttackChar->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 200, 380.f));
	}

	{
		//Set switch

		auto Switch = makeEntity();
		auto s= Switch->addComponent<TextComponent>("Switch");
		s->getText().setOrigin(s->getText().getGlobalBounds().width / 2, s->getText().getGlobalBounds().height / 2);
		Switch->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 400, 300.f));

		switchBox = makeEntity();
		auto sb = switchBox->addComponent<ShapeComponent>();
		sb->setShape<sf::RectangleShape>(Vector2f(40.f, 50.f));
		sb->getShape().setOrigin(sb->getShape().getGlobalBounds().width / 2, sb->getShape().getGlobalBounds().height / 2);
		switchBox->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 400, 380.f));

		SwitchChar = makeEntity();
		auto sc = SwitchChar->addComponent<TextComponent>(txtswitch);
		sc->getText().setOrigin(sc->getText().getGlobalBounds().width / 2, sc->getText().getGlobalBounds().height / 2);
		SwitchChar->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2 + 400, 380.f));

	}

	{
		btnDone = makeButton("Done", Vector2f(150, 60));
		btnDone->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 650.f));
	}
	setLoaded(true);
}

void SettingsGameplayScene::UnLoad() {
	ls::unload();
	Scene::UnLoad();
}

void SettingsGameplayScene::Update(const double& dt)
{

	auto e = Engine::getEvent();

	sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::GetWindow());
	sf::Vector2f worldPos = Engine::GetWindow().mapPixelToCoords(pixelPos);


	if (btnBack->get_components<BtnComponent>()[0]->isSelected())
	{
		Engine::ChangeScene((Scene*)&settings);
	}


	if (walkLeftBox->GetCompatibleComponent<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(worldPos))
	{
		walkLeftBox->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(240, 178, 0));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (e.type == sf::Event::TextEntered)
			{
				if (e.text.unicode < 128)
				{
					txtwalkLeft = toupper(e.text.unicode);
					LeftChar->GetCompatibleComponent<TextComponent>()[0]->SetText(txtwalkLeft);
					LeftChar->GetCompatibleComponent<TextComponent>()[0]->getText().setOrigin(LeftChar->GetCompatibleComponent<TextComponent>()[0]->getText().getGlobalBounds().width / 2, LeftChar->GetCompatibleComponent<TextComponent>()[0]->getText().getGlobalBounds().height / 2);
				}
			}
		}

	}
	else
	{
		walkLeftBox->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(128, 128, 128));
	}



	if (walkRightBox->GetCompatibleComponent<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(worldPos))
	{
		walkRightBox->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(240, 178, 0));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (e.type == sf::Event::TextEntered)
			{
				if (e.text.unicode < 128)
				{
					txtwalkRight = toupper(e.text.unicode);
					RightChar->GetCompatibleComponent<TextComponent>()[0]->SetText(txtwalkRight);
					RightChar->GetCompatibleComponent<TextComponent>()[0]->getText().setOrigin(RightChar->GetCompatibleComponent<TextComponent>()[0]->getText().getGlobalBounds().width / 2, RightChar->GetCompatibleComponent<TextComponent>()[0]->getText().getGlobalBounds().height / 2);
				}
			}
		}
	}
	else
	{
		walkRightBox->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(128, 128, 128));
	}



	if (jumpBox->GetCompatibleComponent<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(worldPos))
	{
		jumpBox->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(240, 178, 0));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (e.type == sf::Event::TextEntered)
			{
				if (e.text.unicode < 128)
				{
					txtjump = toupper(e.text.unicode);
					JumpChar->GetCompatibleComponent<TextComponent>()[0]->SetText(txtjump);
					JumpChar->GetCompatibleComponent<TextComponent>()[0]->getText().setOrigin(JumpChar->GetCompatibleComponent<TextComponent>()[0]->getText().getGlobalBounds().width / 2, JumpChar->GetCompatibleComponent<TextComponent>()[0]->getText().getGlobalBounds().height / 2);
				}
			}
		}
	}
	else
	{
		jumpBox->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(128, 128, 128));
	}



	if (attackBox->GetCompatibleComponent<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(worldPos))
	{
		attackBox->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(240, 178, 0));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (e.type == sf::Event::TextEntered)
			{
				if (e.text.unicode < 128)
				{
					txtattack = toupper(e.text.unicode);
					AttackChar->GetCompatibleComponent<TextComponent>()[0]->SetText(txtattack);
					AttackChar->GetCompatibleComponent<TextComponent>()[0]->getText().setOrigin(AttackChar->GetCompatibleComponent<TextComponent>()[0]->getText().getGlobalBounds().width / 2, AttackChar->GetCompatibleComponent<TextComponent>()[0]->getText().getGlobalBounds().height / 2);
				}
			}
		}
	}
	else
	{
		attackBox->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(128, 128, 128));
	}



	if (switchBox->GetCompatibleComponent<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(worldPos))
	{
		switchBox->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(240, 178, 0));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (e.type == sf::Event::TextEntered)
			{
				if (e.text.unicode < 128)
				{
					txtswitch = toupper(e.text.unicode);
					SwitchChar->GetCompatibleComponent<TextComponent>()[0]->SetText(txtswitch);
					SwitchChar->GetCompatibleComponent<TextComponent>()[0]->getText().setOrigin(SwitchChar->GetCompatibleComponent<TextComponent>()[0]->getText().getGlobalBounds().width / 2, SwitchChar->GetCompatibleComponent<TextComponent>()[0]->getText().getGlobalBounds().height / 2);
				}
			}
		}
	}
	else
	{
		switchBox->GetCompatibleComponent<ShapeComponent>()[0]->getShape().setFillColor(Color(128, 128, 128));
	}


	if (btnDone->get_components<BtnComponent>()[0]->isSelected())
	{
		ofstream output;
		output.open("res/savestates/PlayerControls.txt");
		output << txtwalkLeft << endl;
		output << txtwalkRight << endl;
		output << txtjump << endl;
		output << txtattack << endl;
		output << txtswitch << endl;
		output.close();

		Engine::ChangeScene((Scene*)&settings);
	}
	Scene::Update(dt);
}

void SettingsGameplayScene::Render() 
{
	ls::render(Engine::GetWindow());
	Scene::Render();
}