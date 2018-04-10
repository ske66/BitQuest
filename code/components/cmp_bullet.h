#pragma once
#include <ecm.h>

class BulletComponent : public Component
{
protected:
	double _bulletSpeed; 
	double _bulletDamage;

public:

	explicit BulletComponent(Entity* p);
	
	void moveBullet(double dt);
	void update(double dt);
	void render();

	BulletComponent() = delete;

};
