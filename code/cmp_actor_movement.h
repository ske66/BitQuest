#pragma once
#include <ecm.h>

class ActorMovementComponent : public Component
{
protected:
	bool validMove(const sf::Vector2f&);


public:
	explicit ActorMovementComponent(Entity* p);
	ActorMovementComponent() = delete;

	void move(const sf::Vector2f&);
	void move(float x, float y);

	void render() override {}
	void update(float dt) override;
		
};