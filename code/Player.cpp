#include "Player.h"
#include "Game.h"
#include "System_Renderer.h"

using namespace sf;
using namespace std;

void Player::update(const float dt) {

	Vector2f temp = getPosition();

	Vector2f direction = { 0.0, 0.0 };

	if (Keyboard::isKeyPressed(Keyboard::A))
		direction.x--;

	if (Keyboard::isKeyPressed(Keyboard::D))
		direction.x++;

	move((float)dt * direction * _speed);

	Entity::update(dt);
}

Player::Player() : _speed(200.0f), Entity(make_unique<CircleShape>(25.0f)) {
	_shape->setFillColor(Color::Yellow);
	_shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::render(sf::RenderWindow &window) const {
	Renderer::queue(_shape.get());
}