#include "Game.h"
#include "ecm.h"
#include "cmp_texture_component.h"
#include "cmp_player_movement.h"
#include "cmp_enemy_AI.h"
#define ENEMY_COUNT 1


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
		
		sf::Texture temp;
		temp.loadFromFile("res\\characters\\Bob_spritesheet(75%).png");

		auto player = make_shared<Entity>();
		player->addComponent<PlayerMovementComponent>();
		auto s = player->addComponent<TextureComponent>();
		s->setShape<sf::RectangleShape>(Vector2f(240.f,240.f));
		s->setTexture(temp);
		s->getShape().setTexture(s->getTexture());
		s->getShape().setTextureRect(IntRect(0,0,240,240));
		s->getShape().setOrigin(Vector2f(120.f, 120.f));
		player->setPosition(Vector2f(gameWidth * 0.5f, gameHeight * 0.8f));
		_ents.list.push_back(player);
	}

	{

		sf::Texture temp;
		temp.loadFromFile("res\\characters\\Wizard_spritesheet(75%).png");

		auto enemy = make_shared<Entity>();
		auto s = enemy->addComponent<TextureComponent>();
		s->setShape<sf::RectangleShape>(Vector2f(240.f,240.f));
		s->setTexture(temp);
		s->getShape().setTexture(s->getTexture());
		s->getShape().setOrigin(Vector2f(120.f, 120.f));
		s->getShape().setTextureRect(IntRect(0, 0, 240, 240));
		enemy->setPosition(Vector2f((gameWidth / 2) - 200, gameHeight * 0.8f));
		enemy->addComponent<EnemyAIComponent>();

		_ents.list.push_back(enemy);

	}

}



