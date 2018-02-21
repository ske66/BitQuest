#include "Game.h"
#include "System_Renderer.h"
#include "Entity.h"
#include "Scene.h"

#include "SFML\Graphics.hpp"
#include <iostream>

using namespace sf;
using namespace std;

shared_ptr<Scene> gameScene;
shared_ptr<Scene> menuScene;
shared_ptr<Scene> activeScene;

void Load()
{
	gameScene.reset(new GameScene());
	menuScene.reset(new MenuScene());
	gameScene->load();
	menuScene->load();

	activeScene = menuScene;
}

void Update(RenderWindow &window)
{
	static Clock clock;
	const float dt = clock.restart().asSeconds();
	activeScene->update(dt);
	
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
			return;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))
		window.close();
}

void Render(RenderWindow &window)
{
	activeScene->render();
	Renderer::render();
}

int Main()
{
	RenderWindow window(VideoMode(gameWidth, gameHeight), "BitQuest");

	Renderer::initialise(window);

	Load();
	
	while (window.isOpen())
	{
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}

	return 0;
}