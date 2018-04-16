#pragma once
#include <ecm.h>

class BulletComponent : public Component
{
protected:
	double _bulletSpeed; 
	double _bulletDamage;

public:

	std::shared_ptr<Entity> _player;
	std::shared_ptr<Entity> _gavin;
	explicit BulletComponent(Entity* p);
	
	bool facingRight = true; //
	void moveBullet(double dt);
	void checkContact(double dt);
	void update(double dt);
	void render();

	BulletComponent() = delete;

};
