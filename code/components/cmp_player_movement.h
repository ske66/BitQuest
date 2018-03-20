#include "cmp_actor_movement.h"

class PlayerMovementComponent : public ActorMovementComponent
{
protected:
	float _speed = 200.f;

public:
	explicit PlayerMovementComponent(Entity* p);
	PlayerMovementComponent() = delete;
	void render() override {}
	void update(double dt) override;
	float getSpeed() const;
};