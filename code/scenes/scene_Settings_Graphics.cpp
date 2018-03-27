#include "scene_Settings_Graphics.h"
#include "../components/cmp_text.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_sprite.h"
#include "SFML\Graphics.hpp"
#include "../GameState.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> btnGraphicsBack;

void SettingsGraphicsScene::Load() 
{
	{

		btnGraphicsBack = makeEntity();
		auto b = btnGraphicsBack->addComponent<ShapeComponent>();
		b->setShape<sf::RectangleShape>(Vector2f(100.f, 60.f));
		b->getShape().setOrigin(b->getShape().getGlobalBounds().width / 2, b->getShape().getGlobalBounds().height / 2);
		btnGraphicsBack->setPosition(Vector2f(200.f, 100.f));
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

	setLoaded(true);
}

void SettingsGraphicsScene::UnLoad() {
	cout << "Graphics Settings Unload" << endl;
	Scene::UnLoad();
}

void SettingsGraphicsScene::Update(const double& dt) 
{
	sf::Vector2i pixelPos = sf::Mouse::getPosition(Engine::GetWindow());
	sf::Vector2f worldPos = Engine::GetWindow().mapPixelToCoords(pixelPos);

		if (btnGraphicsBack->GetCompatibleComponent<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(worldPos))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				Engine::ChangeScene((Scene*)&settings);
			}
		}

	Scene::Update(dt);
}

void SettingsGraphicsScene::Render() {

	Scene::Render();
}