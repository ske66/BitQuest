
#pragma once

#include "components/cmp_state_machine.h"

// ENEMY A ////////////////////////////////////////////////////////////////////

class Ghost_IdleState : public State
{
private:
	std::shared_ptr<Entity> _player;

public:

	Ghost_IdleState(std::shared_ptr<Entity> player)
		: _player(player) {}

	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
	
};


class Ghost_ChaseState : public State
{
private:
	std::shared_ptr<Entity> _player;

public:

	Ghost_ChaseState(std::shared_ptr<Entity> player)
		: _player(player) {}

	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};


class Ghost_CastState : public State
{
private:
	std::shared_ptr<Entity> _player;
	bool shot = false;
public:

	double attackRange;
	Ghost_CastState(std::shared_ptr<Entity> player)
		: _player(player) {}

	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};

class Ghost_DeadState : public State
{
private:

public:

	double attackRange;
	Ghost_DeadState(){}

	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};