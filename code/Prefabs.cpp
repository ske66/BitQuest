#include "Prefabs.h"
#include "engine.h"
#include <levelsystem.h>
#include <system_resources.h>

#include "components\cmp_bullet.h"
#include "components\cmp_hurt.h"
#include "goblin_states.h"
#include"components\cmp_object_anim.h"
#include "components\cmp_state_Machine.h"
#include "components\cmp_btn.h"
#include "components\cmp_animation.h"
#include "components\cmp_player_controller.h"
#include "components\cmp_UI.h"
#include "gavin_states.h"
#include "Player_states.h"

using namespace std;
using namespace sf;


//**// Prefab Model \\**\\

/*
This model takes the current Entity->Component model and further enhances it, taking cues from the Unity 3D engine's prefab model. The
model take a number of components and turns them into an entity, this entity is then stored in a list, allowing the user to place the 
entities all across the game without duplicate code.

Our code does the exact same thing, using smart pointers we can create a list of a specific entities such as an enemy and place them
all over our level using the tile Engine to read them into the level, the order for this system goes as follows.


shared_ptr<Entity> makeSomething()
{
	auto something = Engine::GetActiveScene()->makeEntity();  create the entity
	something->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));  set the spawn location of the entity
	something->addTag("something");  give entity a tag for the state machine

	something->addComponent<SomeComponent>();  add component to the entity "something"
	something->addComponent<OtherComponent>();  add another component to the entity "something"

	return something;
}


We can then take this code and spawn it inside one of our levels using the line;

	makeSomething();
*/

shared_ptr<Entity> makePlayer(Vector2f _pos)
{
	auto player = Engine::GetActiveScene()->makeEntity();
	player->setPosition(_pos);
	player->addTag("player");

	auto sm = player->addComponent<StateMachineComponent>();

	sm->addState("idle", make_shared<Player_IdleState>());
	sm->addState("walk_left", make_shared<Player_MoveLeftState>());
	sm->addState("walk_right", make_shared<Player_MoveRightState>());
	sm->addState("Attack", make_shared<Player_AttackState>());
	sm->addState("dead", make_shared<Player_DeadState>());
	sm->changeState("idle");

	player->addComponent<PlayerControlerComponent>();
	player->addComponent<PlayerPhysicsComponent>(Vector2f(120, 160));
	auto a = player->addComponent<AnimationComponent>();
	a->Animation("spritesheets/Bob_spritesheet.png", Vector2f(0, 120), IntRect(0, 0, 240, 240), Vector2u(8, 8));
	a->getSprite().setOrigin(a->getSprite().getGlobalBounds().width / 2, a->getSprite().getGlobalBounds().height / 2);

//	auto h = player->addComponent<HurtComponent>("player");

	return player;
}


//------------------------ state machine test -----------------------------------------------------------
shared_ptr<Entity> makeGavin()
{
	auto gavin = Engine::GetActiveScene()->makeEntity();
	gavin->setPosition(ls::getTilePosition(ls::findTiles(ls::GAVIN)[0]));
	gavin->addTag("gavin");

	auto sm = gavin->addComponent<StateMachineComponent>();

	Engine::GetActiveScene()->ents.find("player")[0];

	sm->addState("idle", make_shared<Gavin_IdleState>(Engine::GetActiveScene()->ents.find("player")[0]));
	sm->addState("chase", make_shared<Gavin_ChaseState>(Engine::GetActiveScene()->ents.find("player")[0]));
	sm->addState("Attack", make_shared<Gavin_AttackState>(Engine::GetActiveScene()->ents.find("player")[0]));

	gavin->addComponent<GavinPhysicsComponent>(Vector2f(120, 160));
	auto a = gavin->addComponent<AnimationComponent>();
	a->Animation("spritesheets/Gavin_spritesheet.png", Vector2f(0, 120), IntRect(0, 0, 240, 240), Vector2u(8, 8));
	a->getSprite().setOrigin(a->getSprite().getGlobalBounds().width / 2, a->getSprite().getGlobalBounds().height / 2);

	sm->changeState("idle");

	return gavin;
}
// ---------------------------------------------------------------------------------------------------------


vector<shared_ptr<Entity>> makeEnemies()
{
	vector<shared_ptr<Entity>> enemies;

	auto goblins = ls::findTiles(ls::ENEMY_GOBLIN);
	for (auto go : goblins)
	{
		auto goblin = Engine::GetActiveScene()->makeEntity();
		goblin->setPosition(ls::getTilePosition(go));
		goblin->addTag("goblin");
		
		auto p = goblin->addComponent<PhysicsComponent>(true, Vector2f(20, 80));
		auto sm = goblin->addComponent<StateMachineComponent>();
		p->getFixture()->GetBody()->SetBullet(true);
	

		sm->addState("chase", make_shared<Goblin_ChaseState>(Engine::GetActiveScene()->ents.find("player")[0]));
		sm->addState("idle", make_shared<Goblin_IdleState>(Engine::GetActiveScene()->ents.find("player")[0]));
		sm->addState("Attack", make_shared<Goblin_AttackState>(Engine::GetActiveScene()->ents.find("player")[0]));
		sm->changeState("idle");

		auto a = goblin->addComponent<AnimationComponent>();
		a->Animation("Spritesheets/Goblin_spritesheet.png", Vector2f(120, 240), IntRect(0, 0, 240, 240), Vector2u(8, 8));
		a->getSprite().setOrigin(a->getSprite().getGlobalBounds().width / 2, a->getSprite().getGlobalBounds().height / 2);

		enemies.push_back(goblin);
	}

	auto orcs = ls::findTiles(ls::ENEMY_ORC);
	for (auto or : orcs)
	{
		auto orc = Engine::GetActiveScene()->makeEntity();
		orc->setPosition(ls::getTilePosition(or ));
		orc->addTag("orc");



		orc->addComponent<PhysicsComponent>(true, Vector2f(100, 200));
		//auto a = orc->addComponent<AnimationComponent>();
		//a->Animation("Spritesheets/Orc_spritesheet.png", Vector2f(120, 240), IntRect(0, 0, 240, 240), Vector2u(8, 8));
		//a->getSprite().setOrigin(a->getSprite().getGlobalBounds().width / 2, a->getSprite().getGlobalBounds().height / 2);

		enemies.push_back(orc);
	}

	auto trolls = ls::findTiles(ls::ENEMY_TROLL);
	for (auto tr : trolls)
	{
		auto troll = Engine::GetActiveScene()->makeEntity();
		troll->setPosition(ls::getTilePosition(tr));
		troll->addTag("troll");



		troll->addComponent<PhysicsComponent>(true, Vector2f(100, 360));
		//auto a = troll->addComponent<AnimationComponent>();
		//a->Animation("Spritesheets/Troll_spritesheet.png", Vector2f(120, 240), IntRect(0, 0, 360, 360), Vector2u(8, 8));
		//a->getSprite().setOrigin(a->getSprite().getGlobalBounds().width / 2, a->getSprite().getGlobalBounds().height / 2);

		enemies.push_back(troll);
	}

	auto skeletons = ls::findTiles(ls::ENEMY_SKELETON);
	for (auto sk : skeletons)
	{
		auto skeleton = Engine::GetActiveScene()->makeEntity();
		skeleton->setPosition(ls::getTilePosition(sk));
		skeleton->addTag("skeleton");


		skeleton->addComponent<PhysicsComponent>(true, Vector2f(100, 200));
		//auto a = skeleton->addComponent<AnimationComponent>();
		//a->Animation("Spritesheets/Skeleton_spritesheet.png", Vector2f(120, 240), IntRect(0, 0, 240, 240), Vector2u(8, 8));
		//a->getSprite().setOrigin(a->getSprite().getGlobalBounds().width / 2, a->getSprite().getGlobalBounds().height / 2);

		enemies.push_back(skeleton);
	}

	auto slimes = ls::findTiles(ls::ENEMY_SLIME);
	for (auto sl : slimes)
	{
		auto slime = Engine::GetActiveScene()->makeEntity();
		slime->setPosition(ls::getTilePosition(sl));
		slime->addTag("slime");


		slime->addComponent<PhysicsComponent>(true, Vector2f(100, 200));
		//auto a = slime->addComponent<AnimationComponent>();
		//a->Animation("Spritesheets/Slime_spritesheet.png", Vector2f(120, 240), IntRect(0, 0, 240, 240), Vector2u(8, 8));
		//a->getSprite().setOrigin(a->getSprite().getGlobalBounds().width / 2, a->getSprite().getGlobalBounds().height / 2);

		enemies.push_back(slime);
	}

	auto ghosts = ls::findTiles(ls::ENEMY_GHOST);
	for (auto gh : ghosts)
	{
		auto ghost = Engine::GetActiveScene()->makeEntity();
		ghost->setPosition(ls::getTilePosition(gh));
		ghost->addTag("ghost");



		ghost->addComponent<PhysicsComponent>(true, Vector2f(100, 200));
		//auto a = ghost->addComponent<AnimationComponent>();
		//	a->Animation("Spritesheets/Ghost_spritesheet.png", Vector2f(120, 240), IntRect(0, 0, 240, 240), Vector2u(8, 8));
		//a->getSprite().setOrigin(a->getSprite().getGlobalBounds().width / 2, a->getSprite().getGlobalBounds().height / 2);

		enemies.push_back(ghost);
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

		auto a = shop->addComponent <ObjectAnimComponent>();
		a->Animation("spritesheets/Shop_spritesheet.png", Vector2f(0,0), IntRect(0, 0, 240, 240), Vector2u(8, 1));
		a->getSprite().setOrigin(0, 0);

		auto t = shop->addComponent<TextComponent>("Press 'E' to enter shop!");
		t->getText().setOrigin(150, 50);

		Mshops.push_back(shop);
	}
	return Mshops;

}

vector<shared_ptr<Entity>> makeTorches()
{
	vector<shared_ptr<Entity>> Mtorches;

	auto torches = ls::findTiles(ls::TORCH);
	for (auto t : torches)
	{
		auto torch = Engine::GetActiveScene()->makeEntity();
		torch->setPosition(ls::getTilePosition(t));
		torch->addTag("torch");

		//auto a = torch->addComponent<AnimationComponent>();
		//a->Animation("spritesheets/Torch.png", Vector2f(0, 0), IntRect(0, 0, 120, 120), Vector2u(8, 1));

		Mtorches.push_back(torch);
	}

	return Mtorches;
}

vector<shared_ptr<Entity>> makeChests()
{
	vector<shared_ptr<Entity>> Mchests;

	auto chests = ls::findTiles(ls::CHEST);
	for (auto c : chests)
	{
		auto chest = Engine::GetActiveScene()->makeEntity();
		chest->setPosition(ls::getTilePosition(c));
		chest->addTag("chest");


		auto s = chest->addComponent <SpriteComponent>();
		s->Sprite("spritesheets/Chest.png", IntRect(0, 0, 120, 120));
		s->getSprite().setOrigin(0, -140);

		Mchests.push_back(chest);
	}
	return Mchests;

}

vector<shared_ptr<Entity>> makeCoins()
{
	vector<shared_ptr<Entity>> Mcoins;

	auto coins = ls::findTiles(ls::COIN);
	for (auto c : coins)
	{
		auto coin = Engine::GetActiveScene()->makeEntity();
		coin->setPosition(ls::getTilePosition(c));
		coin->addTag("coin");


		coin->addComponent<PhysicsComponent>(false, Vector2f(30, 15));
		auto a = coin->addComponent<ObjectAnimComponent>();
		a->Animation("spritesheets/Coin_spritesheet.png", Vector2f(0, -60), IntRect(0, 0, 60, 60), Vector2u(6, 1));
		a->getSprite().setOrigin(0, 0);

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
	e->addTag("UI");
	
	return e;
}

shared_ptr<Entity>makeUIText()
{
	auto t = Engine::GetActiveScene()->makeEntity();
	auto tt = t->addComponent<TextComponent>("x 0");
	tt->getText().setColor(Color::White);

	return t;
}

shared_ptr<Entity>GavinBlast()
{
	auto gb = Engine::GetActiveScene()->makeEntity();
	auto a = gb->addComponent<SpriteComponent>();
	//a->Sprite("magic.png", IntRect(0, 0, 500, 500));

	if (gb->scene->ents.find("player")[0]->getPosition().x < gb->scene->ents.find("gavin")[0]->getPosition().x)
	{
		a->Sprite("magic.png", IntRect(40, 0, -40, 40));
		gb->setPosition(Vector2f(gb->scene->ents.find("gavin")[0]->getPosition().x - 200 , gb->scene->ents.find("gavin")[0]->getPosition().y));
		gb->setRotation(180.f);
	}
	else
	{
		gb->setPosition(Vector2f(gb->scene->ents.find("gavin")[0]->getPosition().x + 200, gb->scene->ents.find("gavin")[0]->getPosition().y));
		a->Sprite("magic.png", IntRect(0, 0, 40, 40));
	}
	
	std::cout << "gavin shooty shoot" << std::endl;
	//gb->addComponent<PhysicsComponent>(false, Vector2f(40, 40));
	gb->addComponent<BulletComponent>();

	return gb;
}