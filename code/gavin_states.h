
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

class Gavin_PrepAttackState : public State
{
private:
	std::shared_ptr<Entity> _player;

public:

	Gavin_PrepAttackState(std::shared_ptr<Entity> player)
		: _player(player) {}

	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};

class Gavin_AttackState : public State
{
private:
	std::shared_ptr<Entity> _player;

public:

	Gavin_AttackState(std::shared_ptr<Entity> player)
		: _player(player) {}

	void enterState(Entity*) noexcept override {};
	void execute(Entity*, double) noexcept override;
};