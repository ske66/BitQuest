#include "scene_Tutorial.h"
#include "../GameState.h"
#include "../code/Prefabs.h"
#include "../components/cmp_animation.h"
#include "../components/cmp_text.h"
#include "engine.h"
#include "levelsystem.h"
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace sf;
using namespace std;

static shared_ptr<Entity> player;
static shared_ptr<Entity> gavin;

static shared_ptr<Entity> eventBox1;


void TutorialScene::Load()
{

	ls::loadLevelFile("res/Tilemaps/tutorial_level.txt", 240.f);

	TilePhysics();

	makeTorches();

	makeEnemies();


	player = makePlayer(ls::getTilePosition(ls::findTiles(ls::START)[0]));

	_view_center = player->getPosition();
	
	gavin = makeGavin();


	makeEnemies();

	coinAmount();

	arrowAmount();

	addUI();

	eventBox1 = makeEventBox(Vector2f(240, 240));
	eventBox1->setPosition(Vector2f(1100, 2760));

	setLoaded(true);
}


void TutorialScene::UnLoad() {
	ls::unload();
	Scene::UnLoad();
}


void TutorialScene::Update(const double& dt)
{
	//auto mousePos = Engine::GetWindow().mapPixelToCoords(Mouse::getPosition(Engine::GetWindow()));
	Vector2f playerPos = player->getPosition();

	if (eventBox1->get_components<ShapeComponent>()[0]->getShape().getGlobalBounds().contains(playerPos))
	{
		//cout << "Touching yooouuuuuuuooou" << endl;

		yes = true;

		//eventBox1->setForDelete(); 
		
		if (yes == true)
		{
			eventBox1->get_components<TextComponent>()[0]->SetText("hello");
			cout << "Touching meeeeeeehhhheeeee" << endl;
		}

	}

	

	//_shapeCmp->getShape().getGlobalBounds().contains(mousePos)



	if (ls::getTileAt(player->getPosition()) == ls::END) {
		Engine::ChangeScene((Scene*)&level1);
	}

	View view(FloatRect(0, 0, Engine::GetWindow().getSize().x, Engine::GetWindow().getSize().y));
	float view_player_distance = sqrt(((player->getPosition().x - _view_center.x) * (player->getPosition().x - _view_center.x)) + ((player->getPosition().y - _view_center.y) * (player->getPosition().y - _view_center.y)));
	if (view_player_distance > 40.f)
		_view_center += (player->getPosition() - _view_center) *(float)dt * 3.5f;
	view.setCenter(_view_center);

	Engine::GetWindow().setView(view);

	Scene::Update(dt);
}

void TutorialScene::Render() {
	ls::render(Engine::GetWindow());
	Scene::Render();
}