#include "scene_Settings.h"
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_btn.h"
#include "../code/Prefabs.h"
#include "SFML\Graphics.hpp"
#include "../GameState.h"

using namespace std;
using namespace sf;

static shared_ptr<Entity> btnBack;
static shared_ptr<Entity> btnGraphics;
static shared_ptr<Entity> btnAudio;
static shared_ptr<Entity> btnGameplay;

double totalTime = 0.0f;
double clickDelay = 0.3f;


void SettingsScene::Load() 
{
	
	//auto background = makeEntity();
	//auto s = background->addComponent<SpriteComponent>();
	//background->setPosition(Vector2f(0, 0));
	//s->Sprite("Background.png", IntRect(0, 0, 6500, 6500));

	{
		auto txtSettings = makeEntity();
		auto t = txtSettings->addComponent<TextComponent>("Settings");
		t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);
		txtSettings->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 100.f));

		btnBack = makeButton("Back", Vector2f(150, 60));
		btnBack->setPosition(Vector2f(Engine::GetWindow().getSize().x / 7, 100.f));

		btnGraphics = makeButton("Graphics", Vector2f(250, 60));
		btnGraphics->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 300.f));

		btnAudio = makeButton("Audio", Vector2f(250, 60));
		btnAudio->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 450.f));

		btnGameplay = makeButton("Graphics", Vector2f(250, 60));
		btnGameplay->setPosition(Vector2f(Engine::GetWindow().getSize().x / 2, 600.f));
	}
	
	setLoaded(true);
}

void SettingsScene::UnLoad() {
	cout << "Settings Unload" << endl;
	Scene::UnLoad();
}

void SettingsScene::Update(const double& dt) 
{

	if (btnBack->get_components<BtnComponent>()[0]->isSelected())
	{
		Engine::ChangeScene((Scene*)&menu);
	}

	if (btnGraphics->get_components<BtnComponent>()[0]->isSelected())
	{
		Engine::ChangeScene((Scene*)&settingsGraphics);
	}

	if (btnAudio->get_components<BtnComponent>()[0]->isSelected())
	{
		Engine::ChangeScene((Scene*)&settingsAudio);
	}

	if (btnGameplay->get_components<BtnComponent>()[0]->isSelected())
	{
		Engine::ChangeScene((Scene*)&settingsGameplay);
	}

	Scene::Update(dt);
}

void SettingsScene::Render() {
	
	Scene::Render();
}
