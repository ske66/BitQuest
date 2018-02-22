#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Entity {
protected:
	std::unique_ptr<sf::Shape> _shape;
	sf::Vector2f _position;
	Entity(std::unique_ptr<sf::Shape> shp);

public:
	Entity() = delete;
	virtual ~Entity() = default;

	virtual void update(const float dt);
	virtual void render(sf::RenderWindow &window) const = 0;

	const sf::Vector2f getPosition();
	void setPosition(const sf::Vector2f &pos);
	void move(const sf::Vector2f &pos);
};

struct EntityManager {
	std::vector<std::shared_ptr<Entity>> list;
	void update(float dt);
	void render(sf::RenderWindow &window);
};