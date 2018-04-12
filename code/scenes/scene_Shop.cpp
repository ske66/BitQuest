#include "scene_Shop.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_btn.h"
#include "../GameState.h"
#include "../code/Prefabs.h"
#include "engine.h"
#include "levelsystem.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;

static shared_ptr<Entity> btnDamage;
static shared_ptr<Entity> btnHealth;
static shared_ptr<Entity> btnHam;
static shared_ptr<Entity> btnArrow;
static shared_ptr<Entity> btnBack;


void ShopScene::Load()
{
	ls::loadLevelFile("res/tilemaps/backgrounds.txt", 240.f);

	//Music
	_musicShop = Resources::get<Music>("Shop_Music.wav");
	_musicShop->play();
	_musicShop->setLoop(true);


	{
		auto txtShop = makeEntity();
		auto t = txtShop->addComponent<TextComponent>("Ye Olde Tesco");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtShop->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 100.f));
		

		btnBack = makeButton("Back", Vector2f(150, 60));
		btnBack->setPosition(Vector2f(Engine::GetWindow().getSize().x / 7, 100.f));
	}

	{
		auto topBar = RectangleShape({ (float)Engine::GetWindow().getSize().x, 80.f });
		topBar.setFillColor(Color::Black);
		topBar.setOrigin(0, 0);
	}

	{
		auto Damage = makeEntity();
		auto d = Damage->addComponent<SpriteComponent>();
		d->Sprite("Shop_Upgrades/DamageUpgrade.png", IntRect(0, 0, 360, 407));
		d->getSprite().setOrigin(d->getSprite().getLocalBounds().width / 2, d->getSprite().getLocalBounds().height / 2);
		Damage->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5, Engine::GetWindow().getSize().y / 2));

		auto txtDamage = makeEntity();
		auto dt = txtDamage->addComponent<TextComponent>("250 Gold");
		dt->getText().setFillColor(Color(240, 178, 0));
		dt->getText().setOrigin(dt->getText().getGlobalBounds().width / 2, dt->getText().getGlobalBounds().height / 2);
		txtDamage->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5, Engine::GetWindow().getSize().y / 2 * 0.55));


		btnDamage = makeButton("Buy Upgrade!", Vector2f(230, 60));
		btnDamage->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5, Engine::GetWindow().getSize().y / 2 * 1.5));
	}

	{
		auto Health = makeEntity();
		auto h = Health->addComponent<SpriteComponent>();
		h->Sprite("Shop_Upgrades/HealthUpgrade.png", IntRect(0, 0, 360, 407));
		h->getSprite().setOrigin(h->getSprite().getLocalBounds().width / 2, h->getSprite().getLocalBounds().height / 2);
		Health->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5 * 2, Engine::GetWindow().getSize().y / 2));

		auto txtHealth = makeEntity();
		auto dt = txtHealth->addComponent<TextComponent>("250 Gold");
		dt->getText().setFillColor(Color(240, 178, 0));
		dt->getText().setOrigin(dt->getText().getGlobalBounds().width / 2, dt->getText().getGlobalBounds().height / 2);
		txtHealth->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5*2, Engine::GetWindow().getSize().y / 2 * 0.55));

		btnHealth = makeButton("Buy Upgrade!", Vector2f(230, 60));
		btnHealth->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5 * 2, Engine::GetWindow().getSize().y / 2 * 1.5));
	}

	{
		auto Ham = makeEntity();
		auto ha = Ham->addComponent<SpriteComponent>();
		ha->Sprite("Shop_Upgrades/HealthFull.png", IntRect(0, 0, 360, 407));
		ha->getSprite().setOrigin(ha->getSprite().getLocalBounds().width / 2, ha->getSprite().getLocalBounds().height / 2);
		Ham->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5 * 3, Engine::GetWindow().getSize().y / 2));

		auto txtHam = makeEntity();
		auto dt = txtHam->addComponent<TextComponent>("25 Gold");
		dt->getText().setFillColor(Color(240, 178, 0));
		dt->getText().setOrigin(dt->getText().getGlobalBounds().width / 2, dt->getText().getGlobalBounds().height / 2);
		txtHam->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5*3, Engine::GetWindow().getSize().y / 2 * 0.55));

		btnHam = makeButton("Buy Ham!", Vector2f(230, 60));
		btnHam->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5 * 3, Engine::GetWindow().getSize().y / 2 * 1.5));
	}

	{
		auto Arrow = makeEntity();
		auto a = Arrow->addComponent<SpriteComponent>();
		a->Sprite("Shop_Upgrades/Arrow.png", IntRect(0, 0, 360, 407));
		a->getSprite().setOrigin(a->getSprite().getLocalBounds().width / 2, a->getSprite().getLocalBounds().height / 2);
		Arrow->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5 * 4, Engine::GetWindow().getSize().y / 2));

		auto txtArrow = makeEntity();
		auto dt = txtArrow->addComponent<TextComponent>("5 Gold");
		dt->getText().setFillColor(Color(240, 178, 0));
		dt->getText().setOrigin(dt->getText().getGlobalBounds().width / 2, dt->getText().getGlobalBounds().height / 2);
		txtArrow->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5*4, Engine::GetWindow().getSize().y / 2 * 0.55));

		btnArrow = makeButton("Buy Arrow!", Vector2f(230, 60));
		btnArrow->setPosition(Vector2f(Engine::GetWindow().getSize().x / 5 * 4, Engine::GetWindow().getSize().y / 2 * 1.5));
	}



	Engine::GetWindow().setView(Engine::GetWindow().getDefaultView());

	setLoaded(true);
}


void ShopScene::UnLoad() {
	_musicShop->stop();
	_musicShop.reset();

	ls::unload();
	Scene::UnLoad();
}

void ShopScene::Update(const double& dt)
{
	Scene::Update(dt);
}


void ShopScene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}