#include "cmp_player_movement.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


PlayerMovementComponent::PlayerMovementComponent(Entity* p)
	: ActorMovementComponent(p) {}

void PlayerMovementComponent::update(double dt) {

	// Movement
	sf::Vector2f direction = { 0.0f, 0.0f };
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		direction.x--;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		direction.x++;
	}
	

	move((float)dt * direction * _speed);

}
float PlayerMovementComponent::getSpeed() const
{
	return _speed;
}