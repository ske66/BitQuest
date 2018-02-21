#include "Enemy.h"
#include "Game.h"
#include "System_Renderer.h"

using namespace sf;
using namespace std;

void Enemy::update(const float dt) {

	Vector2f direction = { 0.0, 0.0 };

	Entity::update(dt);
}

Enemy::Enemy() : _speed(200.0f), Entity(make_unique<CircleShape>(25.f)) {
	_shape->setFillColor(Color::Red);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Enemy::render(sf::RenderWindow &window) const {
	Renderer::queue(_shape.get());
}