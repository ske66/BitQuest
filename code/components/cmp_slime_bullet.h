
#pragma once
#include <ecm.h>
#include "system_physics.h"
#include <Engine.h>

class SlimeBulletComponent : public Component
{
protected:
	float _bulletSpeed;
	float _bulletDamage;

	float _bulletDip;
	float _bulletArc;

public:


	//------------- Physic Bullet arc values
	double TempUnder ;
	double TempUnder2;
	double Over;
	double Under = TempUnder * TempUnder2;
	double SumOf;
	double V;
	double Vx;
	double Viy;
	b2Vec2 Velocity_vector;
	//--------------------------------------

	std::shared_ptr<Entity> _player;


	explicit SlimeBulletComponent(Entity* p);

	bool facingRight = true; //
	void moveBullet(double dt);
	void checkContact(double dt);
	void update(double dt);
	void render();

	SlimeBulletComponent() = delete;

};