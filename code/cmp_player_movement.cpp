#include "cmp_player_movement.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

PlayerMovementComponent::PlayerMovementComponent(Entity* p)
	: ActorMovementComponent(p) {}

void PlayerMovementComponent::update(float dt) {

	// Movement
	sf::Vector2f direction = { 0.0f, 0.0f };
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		direction.x--;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		direction.x++;
	}
	

	move((float)dt * direction * _speed);

}