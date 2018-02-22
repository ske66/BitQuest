#include "Game.h"
#include "Player.h"
#include "ecm.h"
#include "cmp_player_movement.h"
#include "cmp_enemy_AI.h"
#define ENEMY_COUNT 4


using namespace std;
using namespace sf;

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
	text.setString("Almost Pacman");
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
}

void GameScene::respawn() {}

void GameScene::load() 
{

	{
		auto player = make_shared<Entity>();
		
		auto s = player->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(Color::Yellow);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));
		player->setPosition(Vector2f(gameWidth * 0.5f, gameHeight * 0.5f));
		player->addComponent<PlayerMovementComponent>();

		_ents.list.push_back(player);
	}

	const sf::Color enemy_cols[]{ {208, 62, 25},
								{219, 133, 28}, 
								{70, 191, 238},
								{234, 130, 229} };

	for (int i = 0; i < ENEMY_COUNT; ++i)
	{
		auto enemy = make_shared<Entity>();
		auto s = enemy->addComponent<ShapeComponent>();
		s->setShape<sf::CircleShape>(12.f);
		s->getShape().setFillColor(enemy_cols[i % 4]);
		s->getShape().setOrigin(Vector2f(12.f, 12.f));
		enemy->setPosition(Vector2f((gameWidth/2) + (i * 100), gameHeight * 0.8f));
		enemy->addComponent<EnemyAIComponent>();

		_ents.list.push_back(enemy);

	}
}

void ShapeComponent::update(float dt)
{
	_shape->setPosition(_parent->getPosition());
}

void ShapeComponent::render()
{
	Renderer::queue(_shape.get());
}

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p)
	: Component(p), _shape(make_shared<sf::CircleShape>()){}
