#include "scene_Settings_Audio.h"
#include "../components/cmp_text.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_btn.h"
#include "../code/Prefabs.h"
#include "SFML\Graphics.hpp"
#include "../GameState.h"
#include "levelsystem.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> btnBack;
static shared_ptr<Entity> studMaster;
static shared_ptr<Entity> studMusic;
static shared_ptr<Entity> studSFX;
static shared_ptr<Entity> btnDone;

void SettingsAudioScene::Load()
{

	ls::loadLevelFile("res/tilemaps/backgrounds.txt", 240.f);

	{
		//Back button
		auto txtAudio = makeEntity();
		auto t = txtAudio->addComponent<TextComponent>("Audio");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtAudio->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 100.f));

		btnBack = makeButton("Back", Vector2f(150, 60));
		btnBack->setPosition(Vector2f(Engine::GetWindow().getSize().x / 7, 100.f));
	}

	{
		//Master audio slider
		auto txtMaster = makeEntity();
		auto t = txtMaster->addComponent<TextComponent>("Master Volume");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtMaster->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 200.f));

		auto slider = makeEntity();
		auto s = slider->addComponent<SpriteComponent>();
		s->Sprite("Slider.png", IntRect(0, 0, 500, 32));
		s->getSprite().setOrigin(s->getSprite().getGlobalBounds().width / 2, s->getSprite().getGlobalBounds().height / 2);
		slider->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 250.f));

		 studMaster = makeEntity();
		auto st = studMaster->addComponent<SpriteComponent>();
		st->Sprite("stud.png", IntRect(0, 0, 32, 24));
		st->getSprite().setOrigin(st->getSprite().getGlobalBounds().width / 2, st->getSprite().getGlobalBounds().height / 2);
		studMaster->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 250.f));
	}

	{
		//Music audio slider

		auto txtMusic = makeEntity();
		auto t = txtMusic->addComponent<TextComponent>("Music Volume");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtMusic->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 350.f));

		auto slider = makeEntity();
		auto s = slider->addComponent<SpriteComponent>();
		s->Sprite("Slider.png", IntRect(0, 0, 500, 32));
		s->getSprite().setOrigin(s->getSprite().getGlobalBounds().width / 2, s->getSprite().getGlobalBounds().height / 2);
		slider->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 400.f));

		 studMusic = makeEntity();
		auto st = studMusic->addComponent<SpriteComponent>();
		st->Sprite("stud.png", IntRect(0, 0, 32, 24));
		st->getSprite().setOrigin(st->getSprite().getGlobalBounds().width / 2, st->getSprite().getGlobalBounds().height / 2);
		studMusic->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 400.f));
	}

	{
		//SFX audio slider

		auto txtSFX = makeEntity();
		auto t = txtSFX->addComponent<TextComponent>("SFX Audio");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtSFX->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 500.f));

		auto slider = makeEntity();
		auto s = slider->addComponent<SpriteComponent>();
		s->Sprite("Slider.png", IntRect(0, 0, 500, 32));
		s->getSprite().setOrigin(s->getSprite().getGlobalBounds().width / 2, s->getSprite().getGlobalBounds().height / 2);
		slider->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 550.f));

		 studSFX = makeEntity();
		auto st = studSFX->addComponent<SpriteComponent>();
		st->Sprite("stud.png", IntRect(0, 0, 32, 24));
		st->getSprite().setOrigin(st->getSprite().getGlobalBounds().width / 2, st->getSprite().getGlobalBounds().height / 2);
		studSFX->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 550.f));
	}

	{
		//Save settings

		btnDone = makeButton("Done", Vector2f(150, 60));
		btnDone->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 650.f));

	}

	setLoaded(true);
}

void SettingsAudioScene::UnLoad() {
	ls::unload();
	Scene::UnLoad();
}

void SettingsAudioScene::Update(const double& dt)
{
		sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::GetWindow());
		sf::Vector2f worldPos = Engine::GetWindow().mapPixelToCoords(pixelPos);

		if (btnBack->get_components<BtnComponent>()[0]->isSelected())
		{
			Engine::ChangeScene((Scene*)&settings);
		}


		if (btnDone->get_components<BtnComponent>()[0]->isSelected())
		{
			Engine::ChangeScene((Scene*)&settings);
		}


		//Slider lock, gets positon of mouse and only lets the slider move alone the x-axis, stops when it hits a certain Position Left & Right
			if (studMaster->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getGlobalBounds().contains(worldPos))
			{

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					studMaster->setPosition(Vector2f(worldPos.x, 250));

					if (studMaster->getPosition().x > 860.f)
					{
						studMaster->setPosition(Vector2f(860, 250));
					}

					if (studMaster->getPosition().x < 430.f)
					{
						studMaster->setPosition(Vector2f(430, 250));
					}
				}
			}

			if (studMusic->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getGlobalBounds().contains(worldPos))
			{

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					studMusic->setPosition(Vector2f(worldPos.x, 400));

					if (studMusic->getPosition().x > 860.f)
					{
						studMusic->setPosition(Vector2f(860, 400));
					}

					if (studMusic->getPosition().x < 430.f)
					{
						studMusic->setPosition(Vector2f(430, 400));
					}
				}
			}

			if (studSFX->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getGlobalBounds().contains(worldPos))
			{

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					studSFX->setPosition(Vector2f(worldPos.x, 550));

					if (studSFX->getPosition().x > 860.f)
					{
						studSFX->setPosition(Vector2f(860, 550));
					}

					if (studSFX->getPosition().x < 430.f)
					{
						studSFX->setPosition(Vector2f(430, 550));
					}
				}
			}

	Scene::Update(dt);
}

void SettingsAudioScene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}