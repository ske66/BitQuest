#include "Prefabs.h"
#include "engine.h"
#include <levelsystem.h>
#include <system_resources.h>

#include "components\cmp_btn.h"
#include "components\cmp_animation.h"
#include "components\cmp_player_controller.h"
#include "components\cmp_state.h"
#include "components\cmp_general_AI.h"
#include "components\cmp_gavin_AI.h"
#include "components\cmp_UI.h"


using namespace std;
using namespace sf;

shared_ptr<Entity> makePlayer()
{
	auto player = Engine::GetActiveScene()->makeEntity();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));
	player->addTag("player");

	player->addComponent<StateComponent>();
	player->addComponent<PlayerControlerComponent>();
	player->addComponent<PlayerPhysicsComponent>(Vector2f(120,220));
	auto a = player->addComponent<AnimationComponent>();
	a->Animation("spritesheets/Bob_spritesheet.png", Vector2f(0, 120), IntRect(0,0,240,240),Vector2u(8,8));
	a->getSprite().setOrigin(a->getSprite().getGlobalBounds().width / 2, a->getSprite().getGlobalBounds().height / 2);

	return player;
}

shared_ptr<Entity> makeGavin()
{
	auto gavin = Engine::GetActiveScene()->makeEntity();
	gavin->setPosition(ls::getTilePosition(ls::findTiles(ls::GAVIN)[0]));
	gavin->addTag("gavin");

	gavin->addComponent<StateComponent>();
	gavin->addComponent<GavinAiComponent>();
	gavin->addComponent<GavinPhysicsComponent>(Vector2f(120, 240));
	auto a = gavin->addComponent<AnimationComponent>();
	a->Animation("spritesheets/Gavin_spritesheet.png", Vector2f(0, 120), IntRect(0, 0, 240, 240), Vector2u(8, 8));
	a->getSprite().setOrigin(a->getSprite().getGlobalBounds().width / 2, a->getSprite().getGlobalBounds().height / 2);

	return gavin;
}



vector<shared_ptr<Entity>> makeEnemies()
{
	vector<shared_ptr<Entity>> enemies;

	auto goblins = ls::findTiles(ls::ENEMY_GOBLIN);
	for (auto go : goblins)
	{
		auto goblin = Engine::GetActiveScene()->makeEntity();
		goblin->setPosition(ls::getTilePosition(go));
		goblin->addTag("goblin");

		goblin->addComponent<StateComponent>();
		goblin->addComponent<GeneralAiComponent>();
		goblin->addComponent<PhysicsComponent>(true, Vector2f(100,200));
		auto a = goblin->addComponent<AnimationComponent>();
		a->Animation("Spritesheets/Goblin_spritesheet.png", Vector2f(120, 240), IntRect(0, 0, 240, 240), Vector2u(8, 8));
		a->getSprite().setOrigin(a->getSprite().getGlobalBounds().width / 2, a->getSprite().getGlobalBounds().height / 2);
	
		enemies.push_back(goblin);
	}

	return enemies;

}

vector<shared_ptr<Entity>> makeShops()
{
	vector<shared_ptr<Entity>> Mshops;
	
	auto shops = ls::findTiles(ls::SHOP);
	for (auto s : shops)
	{
		auto shop = Engine::GetActiveScene()->makeEntity();
		shop->setPosition(ls::getTilePosition(s));
		shop->addTag("Shop");

		shop->addComponent<StateComponent>();
		auto a = shop->addComponent <AnimationComponent>();
		a->Animation("spritesheets/Shop_spritesheet.png", Vector2f(0,0), IntRect(0, 0, 240, 240), Vector2u(8, 1));
		
		auto f = shop->addComponent<AnimationComponent>();
		f->Animation("spritesheets/flicker.png", Vector2f(30, 0), IntRect(0, 0, 240, 240), Vector2u(10, 1));

		auto t = shop->addComponent<TextComponent>();
		t->SetText("Press Enter to open shop");
		t->getText().setCharacterSize(16);
		t->getText().setOrigin(60, 40);
		
		Mshops.push_back(shop);
	}
	return Mshops;
	
}

vector<shared_ptr<Entity>>makeTorches()
{
	vector<shared_ptr<Entity>> Mtorches;

	auto torches = ls::findTiles(ls::TORCH);
	for (auto t : torches)

	{
	auto torch = Engine::GetActiveScene()->makeEntity();
	torch->setPosition(ls::getTilePosition(t));
	torch->addTag("torch");

	torch->addComponent<StateComponent>();
	auto a = torch->addComponent<AnimationComponent>();	
	a->Animation("spritesheets/Torch.png", Vector2f(0,0), IntRect(0, 0, 120, 120), Vector2u(8, 1));

	auto f = torch->addComponent<AnimationComponent>();
	f->Animation("spritesheets/flicker.png", Vector2f(60, 60), IntRect(0, 0, 240, 240), Vector2u(10, 1));
	
	Mtorches.push_back(torch);

	}
	return Mtorches;
}

vector<shared_ptr<Entity>> makeChest()
{
	vector<shared_ptr<Entity>> Mchests;

	auto chests = ls::findTiles(ls::CHEST);
	for (auto c : chests)
	{
		auto chest = Engine::GetActiveScene()->makeEntity();
		chest->setPosition(ls::getTilePosition(c));
		chest->addTag("chest");

		chest->addComponent<StateComponent>();
		auto s = chest->addComponent <SpriteComponent>();
		s->Sprite("spritesheets/Chest.png", IntRect(0,0,240,240));
		s->getSprite().setOrigin(0,0);

		Mchests.push_back(chest);
	}
	return Mchests;

}

vector<shared_ptr<Entity>> makeCoin()
{
	vector<shared_ptr<Entity>> Mcoins;
	
	auto coins = ls::findTiles(ls::COIN);
		for (auto c : coins)
		{
		auto coin = Engine::GetActiveScene()->makeEntity();
		coin->setPosition(ls::getTilePosition(c));
		coin->addTag("coin");

		coin->addComponent<StateComponent>();
		coin->addComponent<PhysicsComponent>(false, Vector2f(30, 15));
		auto a = coin->addComponent <AnimationComponent>();
		a->Animation("spritesheets/Coin_spritesheet.png", Vector2f(0, -60), IntRect(0, 0, 60, 60), Vector2u(6, 1));
		a->getSprite().setOrigin(0,0);

		Mcoins.push_back(coin);
		}
		return Mcoins;

}



shared_ptr<Entity> makeButton(string text, Vector2f bounds)
{

	auto button = Engine::GetActiveScene()->makeEntity();
	button->addTag("button");

	auto s = button->addComponent<ShapeComponent>();
	s->setShape<RectangleShape>(Vector2f(bounds));
	s->getShape().setFillColor(Color::Transparent);
	s->getShape().setOrigin(s->getShape().getGlobalBounds().width / 2, s->getShape().getGlobalBounds().height / 2);

	auto u = button->addComponent<ShapeComponent>();
	u->setShape<RectangleShape>(Vector2f(bounds.x, 5.f));
	u->getShape().setFillColor(Color(128, 128, 128));
	u->getShape().setOrigin(u->getShape().getGlobalBounds().width / 2, u->getShape().getGlobalBounds().height / 2 - 30);
	
	auto t = button->addComponent<TextComponent>(text);
	t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);

	button->addComponent<BtnComponent>(s, t, u);

	return button;
}

void TilePhysics()
{
	auto walls = ls::findTiles(ls::WALL);
	for (auto w : walls) {
		auto pos = ls::getTilePosition(w);
		pos += Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2);
		auto e = Engine::GetActiveScene()->makeEntity();
		e->setPosition(pos);
		e->addComponent<PhysicsComponent>(false, Vector2f(ls::getTileSize(), ls::getTileSize()));
	}

	auto floor = ls::findTiles(ls::FLOOR);
	for (auto f : floor) {
		auto pos = ls::getTilePosition(f);
		pos += Vector2f(ls::getTileSize() / 2, ls::getTileSize() / 2);
		auto e = Engine::GetActiveScene()->makeEntity();
		e->setPosition(pos);
		e->addComponent<PhysicsComponent>(false, Vector2f(ls::getTileSize(), ls::getTileSize()));
	}
}

shared_ptr<Entity>addUI()
{
	auto e = Engine::GetActiveScene()->makeEntity();
	e->addComponent<UIComponent>();
	return e;
}