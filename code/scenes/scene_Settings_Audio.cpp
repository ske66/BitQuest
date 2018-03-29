#include "scene_Settings_Audio.h"
#include "../components/cmp_text.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_sprite.h"
#include "SFML\Graphics.hpp"
#include "../GameState.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> btnAudioBack;
static shared_ptr<Entity> studMaster;
static shared_ptr<Entity> studMusic;
static shared_ptr<Entity> studSFX;
static shared_ptr<Entity> doneText;

double totalTimeAudio = 0.0f; 
double clickDelayAudio = 0.2f;

void SettingsAudioScene::Load()
{
	
	{
		btnAudioBack = makeEntity();
		auto b = btnAudioBack->addComponent<ShapeComponent>();
		b->setShape<sf::RectangleShape>(Vector2f(100.f, 60.f));
		b->getShape().setOrigin(b->getShape().getGlobalBounds().width / 2, b->getShape().getGlobalBounds().height / 2);
		btnAudioBack->setPosition(Vector2f(200.f, 100.f));
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
		auto txtAudio = makeEntity();
		auto t = txtAudio->addComponent<TextComponent>("Audio");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtAudio->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 100.f));
	}

	{
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

		auto done = makeEntity();
		auto d = done->addComponent<SpriteComponent>();
		d->Sprite("button.png", IntRect(0, 0, 300, 40));
		d->getSprite().setOrigin(d->getSprite().getGlobalBounds().width / 2, d->getSprite().getGlobalBounds().height / 2);
		done->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 650.f));

		doneText = makeEntity();
		auto dt = doneText->addComponent<TextComponent>("Done");
		dt->getText().setOrigin(dt->getText().getGlobalBounds().width / 2, dt->getText().getGlobalBounds().height / 2);
		doneText->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 650.f));

	}

	setLoaded(true);
}

void SettingsAudioScene::UnLoad() {
	cout << "Audio Settings Unload" << endl;
	Scene::UnLoad();
}

void SettingsAudioScene::Update(const double& dt)
{
	auto e = Engine::getEvent();

	totalTimeAudio += dt;

		sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::GetWindow());
		sf::Vector2f worldPos = Engine::GetWindow().mapPixelToCoords(pixelPos);


		if (totalTimeAudio >= clickDelayAudio)
		{
			totalTimeAudio -= clickDelayAudio;

			if (btnAudioBack->GetCompatibleComponent<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(worldPos))
			{
				if (e.MouseButtonPressed)
				{
					if (e.mouseButton.button == sf::Mouse::Left)
					{
						cout << "Yer in" << endl;
						Engine::ChangeScene((Scene*)&settings);
					}
				}

			}
		}

			if (studMaster->GetCompatibleComponent<SpriteComponent>()[0]->getSprite().getGlobalBounds().contains(worldPos))
			{

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					studMaster->setPosition(Vector2f(worldPos.x, 250));

					cout << studMaster->getPosition() << endl;

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

					cout << studMusic->getPosition() << endl;

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

					cout << studSFX->getPosition() << endl;

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

			if (doneText->GetCompatibleComponent<TextComponent>()[0]->getText().getGlobalBounds().contains(worldPos))
			{
				doneText->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(240, 178, 0));

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{

					//save the box's states

					Engine::ChangeScene((Scene*)&settings);
				}
			}
			else
			{
				doneText->GetCompatibleComponent<TextComponent>()[0]->getText().setFillColor(Color(192, 192, 192));
			}


	Scene::Update(dt);
		
}

void SettingsAudioScene::Render() {

	Scene::Render();
}