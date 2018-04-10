#pragma once
#include <ecm.h>

class BulletComponent : public Component
{
protected:
	float _bulletSpeed; 
	float _bulletDamage;

public:

	explicit BulletComponent(Entity* p);
	

	void update(double dt);
	void render();

	BulletComponent() = delete;

};
