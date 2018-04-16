
#pragma once

#include "components/cmp_state_machine.h"

// ENEMY A ////////////////////////////////////////////////////////////////////

class Gavin_IdleState : public State
{
private:
	std::shared_ptr<Entity> _player;

public:

	Gavin_IdleState(std::shared_ptr<Entity> player)
		: _player(player) {}

	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
	
};


class Gavin_ChaseState : public State
{
private:
	std::shared_ptr<Entity> _player;

public:

	Gavin_ChaseState(std::shared_ptr<Entity> player)
		: _player(player) {}

	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};


class Gavin_CastState : public State
{
private:
	std::shared_ptr<Entity> _player;
	bool shot = false;
public:

	double attackRange;
	Gavin_CastState(std::shared_ptr<Entity> player)
		: _player(player) {}

	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};

class Gavin_DeadState : public State
{
private:

public:

	double attackRange;
	Gavin_DeadState(){}

	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};