#pragma once
#include <ecm.h>

class StateComponent : public Component
{
protected:
	bool isWalkingRight;
	bool isWalkingLeft;
	bool isAttacking;
	bool isJumping;
	bool isIdle;
	double _totalTime;
	double _switchTime;

public:

	void setWalkingRight();
	void setWalkingLeft();
	void setJumping();
	void setAttacking();
	void setIdle();

	bool getWalkingRight();
	bool getWalkingLeft();
	bool getJumping();
	bool getAttacking();
	bool getIdle();

	explicit StateComponent(Entity* p);
	StateComponent() = delete;

	void update(double dt);
	void render() override;

};