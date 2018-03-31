#include "engine.h"
#include "maths.h"
#include "../code/GameState.h"
#include "system_physics.h"
#include "system_Renderer.h"
#include "system_resources.h"
#include <SFML\Graphics.hpp>
#include <future>
#include <vector>
#include <iostream>
#include <stdexcept>

using namespace sf;
using namespace std;
Scene* Engine::_activeScene = nullptr;
std::string Engine::_gameName;



static bool loading = false;
static float loadingspinner = 0.f;
static float loadingTime;
static RenderWindow* _window;
static Event* _event;

Texture spritesheet;
Sprite goblin;


float switchtime;
IntRect uvRect = IntRect(240, 0, 240, 240);
sf::Vector2u currentimage;
float totalTime;
sf::Vector2u imagecount(8,8);


void Loading_Load()
{
	string monster;
	const string monster_cols[]{ "goblin", "orc", "troll", "skeleton", "slime", "ghost" };
	monster = (monster_cols[2]);

	spritesheet.loadFromFile("res/textures/" + monster +"_spritesheet.png");
	goblin.setTexture(spritesheet);
	goblin.setTextureRect(uvRect);
	goblin.setOrigin(0, 120);

	switchtime = 0.045f;

	totalTime = 0.f;

	uvRect.width = spritesheet.getSize().x / float(imagecount.x);
	uvRect.width = spritesheet.getSize().y / float(imagecount.y);

}

void Loading_update(float dt, const Scene* const scn) {
	Loading_Load();

	if (scn->isLoaded()) {
		loading = false;
	}
	else {

		totalTime += dt;

		if (totalTime >= switchtime)
		{
			totalTime -= switchtime;

			currentimage.x++;

			if (currentimage.x >= imagecount.x)
			{
				currentimage.x = 0;
				
				cout << "animation restarted" << endl;
			}
		}

		uvRect.left = currentimage.x * uvRect.width;
		uvRect.top = currentimage.y *  uvRect.height;

		goblin.setTextureRect(uvRect);
		goblin.setOrigin(Engine::GetWindow().getSize().x / 2, Engine::GetWindow().getSize().y / 2);
		goblin.setPosition(Engine::GetWindow().getSize().x - 125, Engine::GetWindow().getSize().y / 2 + 200);

	}
}
void Loading_render() {

	static Text t("Loading...", *Resources::get<sf::Font>("Wonder.ttf"));
	t.setOrigin(Engine::GetWindow().getSize().x / 2, Engine::GetWindow().getSize().y / 2);
	t.setPosition(Engine::GetWindow().getSize().x - 125, 900.f);

	Renderer::queue(&t);
	Renderer::queue(&goblin);
}

float frametimes[256] = {};
uint8_t ftc = 0;

void Engine::Update() {
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();
	{
		frametimes[++ftc] = dt;
		static string avg = _gameName + " FPS:";
		if (ftc % 50 == 0) {
			double davg = 0;
			for (const auto t : frametimes) {
				davg += t;
			}
			davg = 1.0 / (davg / 255.0);
			_window->setTitle(avg + toStrDecPt(2, davg));
		}
	}

	if (loading) {
		Loading_update(dt, _activeScene);
	}
	else if (_activeScene != nullptr) {
		Physics::update(dt);
		_activeScene->Update(dt);
	}
}

void Engine::Render(RenderWindow& window) {
	if (loading) {
		Loading_render();
	}
	else if (_activeScene != nullptr) {
		_activeScene->Render();
	}

	Renderer::render();
}

void Engine::Start(unsigned int width, unsigned int height,
	const std::string& gameName, Scene* scn) {
	RenderWindow window(VideoMode(width, height), gameName);
	Event event;
	_gameName = gameName;
	_window = &window;
	_event = &event;
	Renderer::initialise(window);
	Physics::initialise();
	ChangeScene(scn);

	while (window.isOpen()) {

		
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		window.clear();
		Update();
		Render(window);
		window.display();
	}
	if (_activeScene != nullptr) {
		_activeScene->UnLoad();
		_activeScene = nullptr;
	}
	window.close();
	Physics::shutdown();
	Renderer::shutdown();
}

std::shared_ptr<Entity> Scene::makeEntity() {
	auto e = make_shared<Entity>(this);
	ents.list.push_back(e);
	return std::move(e);
}

void Engine::setVsync(bool b) { _window->setVerticalSyncEnabled(b); }

void Engine::ChangeScene(Scene* s) {
	cout << "Eng: changing scene: " << s << endl;
	auto old = _activeScene;
	_activeScene = s;

	if (old != nullptr) {
		old->UnLoad(); // todo: Unload Async
	}

	if (!s->isLoaded()) {
		cout << "Eng: Entering Loading Screen\n";
		loadingTime = 0;
		_activeScene->Load();
		loading = true;
	}
}

void Scene::Update(const double& dt) { ents.update(dt); }

void Scene::Render() { ents.render(); }

bool Scene::isLoaded() const {
	{
		std::lock_guard<std::mutex> lck(_loaded_mtx);
		// Are we already loading asynchronously?
		if (_loaded_future.valid() // yes
			&&                     // Has it finished?
			_loaded_future.wait_for(chrono::seconds(0)) ==
			future_status::ready) {
			// Yes
			_loaded_future.get();
			_loaded = true;
		}
		return _loaded;
	}
}
void Scene::setLoaded(bool b) {
	{
		std::lock_guard<std::mutex> lck(_loaded_mtx);
		_loaded = b;
	}
}

void Scene::UnLoad() {
	ents.list.clear();
	setLoaded(false);
}

void Scene::LoadAsync() { _loaded_future = std::async(&Scene::Load, this); }

sf::Vector2u Engine::getWindowSize() { return _window->getSize(); }

sf::RenderWindow& Engine::GetWindow() { return *_window; }

sf::Event& Engine::getEvent() { return *_event; }

namespace timing {
	// Return time since Epoc
	long long now() {
		return std::chrono::high_resolution_clock::now()
			.time_since_epoch()
			.count();
	}
	// Return time since last() was last called.
	long long last() {
		auto n = now();
		static auto then = now();
		auto dt = n - then;
		then = n;
		return dt;
	}
} // namespace timing

Scene::~Scene() { UnLoad(); }

Scene* Engine::GetActiveScene()
	{
		return _activeScene;
	}
