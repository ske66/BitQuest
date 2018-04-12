
#pragma once
#include <ecm.h>

class PlayerBulletComponent : public Component
{
protected:
	double _bulletSpeed;
	double _bulletDamage;

public:

	std::shared_ptr<Entity> _player;
	explicit PlayerBulletComponent(Entity* p);

	bool facingRight = true; //
	void moveBullet(double dt);
	void checkContact(double dt);
	void update(double dt);
	void render();

	PlayerBulletComponent() = delete;

};