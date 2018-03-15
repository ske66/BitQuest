#include "Game.h"
#include "ecm.h"
#include "sys_physics.h"
#include "cmp_physics.h"
#include "cmp_player_physics.h"
#include "cmp_texture_component.h"
#include "cmp_player_movement.h"
#include "cmp_enemy_AI.h"
#include "levelsystem.h"
#define GOBLIN_COUNT 4
#define TROLL_COUNT 1
#define ORC_COUNT 2





using namespace std;
using namespace sf;

vector<shared_ptr<Entity>> goblins;
vector<shared_ptr<Entity>> orcs;
vector<shared_ptr<Entity>> trolls;
vector<shared_ptr<Entity>> walls;

void MenuScene::update(float dt) 
{
	if (Keyboard::isKeyPressed(Keyboard::Space)) 
	{
		activeScene = gameScene;
	}
	Scene::update(dt);
}

void MenuScene::render() 
{
	Scene::render();
	//Renderer::queue(&text); //apparently this doesn't go here but the text wont render on the screen!?
}

void MenuScene::load() 
{
	Font font;
	font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setString("Bit_Quest");
	text.setColor(Color::White);
	text.setPosition((gameWidth * 0.5f) - (text.getLocalBounds().width * 0.5f), 0);
	
}


void GameScene::update(float dt) 
{
	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		activeScene = menuScene;
	}
	Scene::update(dt);

}

void GameScene::render() 
{
	Scene::render();
	ls::render(Renderer::getWindow());
}

void GameScene::respawn() {


	auto player = make_shared<Entity>();
	player->setPosition(ls::getTilePosition(ls::findTiles(ls::START)[0]));

	sf::Texture temp_bob;
	temp_bob.loadFromFile("res\\characters\\Bob_spritesheet.png"); //temporary texture staorage for load is destroyed as soon as scope left

	auto s = player->addComponent<TextureComponent>();
	s->setShape<sf::RectangleShape>(Vector2f(240.f, 240.f));
	s->setTexture(temp_bob); //setting texture component equal to temporary texture
	s->getShape().setTexture(s->getTexture());
	s->getShape().setTextureRect(IntRect(0, 0, 240, 240));
	s->getShape().setOrigin(Vector2f(120.f, 120.f));

	player->addComponent<PlayerPhysicsComponent>(Vector2f(100.f, 220.f));

	_ents.list.push_back(player);


	//Goblin Spawning
	auto goblin_spawns = ls::findTiles(ls::ENEMY_GOBLIN);
	for (auto& g : goblins) {
		g->setPosition(ls::getTilePosition(goblin_spawns[rand() % GOBLIN_COUNT]));
	}

	//Orc Spawning
	sf::Texture temp_orc;
	temp_orc.loadFromFile("res\\characters\\Orc_spritesheet.png"); //temporary texture staorage for load is destroyed as soon as scope left

	auto orc_spawns = ls::findTiles(ls::ENEMY_ORC);
	for (auto& o : orcs) {
		o->setPosition(ls::getTilePosition(orc_spawns[rand() % ORC_COUNT]));
		o->addComponent<ActorMovementComponent>();

		auto s = o->addComponent<TextureComponent>();
		s->setShape<sf::RectangleShape>(Vector2f(240.f, 240.f));
		s->setTexture(temp_orc); //setting texture component equal to temporary texture
		s->getShape().setTexture(s->getTexture());
		s->getShape().setTextureRect(IntRect(0, 0, 240, 240));
		s->getShape().setOrigin(Vector2f(120.f, 120.f));
	}

	//Troll Spawning
	auto troll_spawns = ls::findTiles(ls::ENEMY_TROLL);
	for (auto& t : trolls) {
		t->setPosition(ls::getTilePosition(troll_spawns[rand() % TROLL_COUNT]));
		t->addComponent<ActorMovementComponent>();
	}




	//Wall Spawning
	auto wall_spawn = ls::findTiles(ls::WALL);
	for (auto& w : walls)
	{
		w->setPosition(ls::getTilePosition(wall_spawn[rand() % walls.size()]));
	}

}


void GameScene::load() 
{
	
	ls::loadLevelFile("res/level_1.txt", 25.f);

	
		
		for (int i = 0; i < walls.size(); ++i){
			auto wall = make_shared<Entity>();
			auto s = wall ->addComponent<TextureComponent>();
			s->setShape<RectangleShape>(Vector2f(25.f, 25.f));
			s->getShape().setFillColor(sf::Color::Yellow);
			wall->addComponent<PhysicsComponent>(false, Vector2f(25.f, 25.f));

			_ents.list.push_back(wall);
			walls.push_back(wall);
			
		}
	

		sf::Texture temp;
		temp.loadFromFile("res\\characters\\Goblin_spritesheet.png");

	for (int i = 0; i < GOBLIN_COUNT; ++i) {
		auto goblin = make_shared<Entity>();
		auto s = goblin->addComponent<TextureComponent>();
		s->setShape<sf::RectangleShape>(Vector2f(240.f, 240.f));
		s->setTexture(temp);
		s->getShape().setTexture(s->getTexture());
		s->getShape().setTextureRect(IntRect(0, 0, 240, 240));
		s->getShape().setOrigin(Vector2f(120.f, 120.f));
		
		goblin->addComponent<EnemyAIComponent>();

		_ents.list.push_back(goblin);
		goblins.push_back(goblin);
	}


	for (int i = 0; i < ORC_COUNT; ++i) {
		auto orc = make_shared<Entity>();
		auto s = orc->addComponent<TextureComponent>();
		s->setShape<sf::RectangleShape>(Vector2f(240.f, 240.f));
		s->getShape().setFillColor(sf::Color::Magenta);
		s->getShape().setOrigin(Vector2f(0.0f, 0.0f));


		orc->addComponent<EnemyAIComponent>();

		_ents.list.push_back(orc);
		orcs.push_back(orc);
	}

	


	for (int i = 0; i < TROLL_COUNT; ++i) {
		auto troll = make_shared<Entity>();
		auto s = troll->addComponent<TextureComponent>();
		s->setShape<sf::RectangleShape>(Vector2f(240.f, 240.f));
		s->getShape().setFillColor(sf::Color::Red);
		s->getShape().setOrigin(Vector2f(0.0f, 0.0f));

		troll->addComponent<PhysicsComponent>(true , Vector2f(120.f,200.f));
		troll->addComponent<EnemyAIComponent>();

		_ents.list.push_back(troll);
		trolls.push_back(troll);
	}

	respawn();

}




