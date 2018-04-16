
#pragma once
#include <ecm.h>

class PlayerBulletComponent : public Component
{
protected:
	float _bulletSpeed;
	float _bulletDamage;

	float _bulletDip;
	float _bulletArc;
public:

	std::vector<std::shared_ptr<Entity>> _slimes;
	std::vector<std::shared_ptr<Entity>> _trolls;
	std::vector<std::shared_ptr<Entity>> _orcs;
	std::shared_ptr<Entity> _player;
	explicit PlayerBulletComponent(Entity* p);

	bool facingRight = true; //
	void moveBullet(double dt);
	void checkContact(double dt);
	void update(double dt);
	void render();

	PlayerBulletComponent() = delete;

};