#include "cmp_enemy_ai.h"

using namespace sf;
using namespace std;

EnemyAIComponent::EnemyAIComponent(Entity* p)
	: ActorMovementComponent(p) {}

void EnemyAIComponent::update(float dt) {

	sf::Vector2f direction = { 0.0f, 0.0f };
	
	direction.x = rand() % 2 + 0 - 1;
	direction.y = rand() % 2 + 0 - 1;
	
	
	move((float)dt * direction * _speed);

}