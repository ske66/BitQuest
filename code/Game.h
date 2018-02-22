#pragma once

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "ecm.h"

constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 600;

extern std::shared_ptr<Scene> gameScene;
extern std::shared_ptr<Scene> menuScene;
extern std::shared_ptr<Scene> activeScene;


class MenuScene : public Scene {
private:
	sf::Text text;

public:
	MenuScene() = default;
	void update(float dt) override;
	void render() override;
	void load() override;
};

class GameScene : public Scene {
private:
	sf::Text text;
	sf::Clock scoreClock;
	void respawn();

public:
	GameScene() = default;
	void update(float dt) override;
	void render() override;
	void load() override;
};


class ShapeComponent : public Component
{
protected:
	std::shared_ptr<sf::Shape> _shape;
public:
	ShapeComponent() = delete;
	explicit ShapeComponent(Entity *p);

	void update(float dt) override;
	void render() override;

	sf::Shape &getShape() const;
	
	template <typename T, typename... Targs>
	void setShape(Targs... params) 
	{
		_shape.reset(new T(params...));
	}
};
