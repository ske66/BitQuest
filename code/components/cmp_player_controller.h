#include "ecm.h"
#include "engine.h"
#include <SFML/Window/Keyboard.hpp>
#include "cmp_state.h"
#include "cmp_player_physics.h"
#include "cmp_gavin_physics.h"


class PlayerControlerComponent : public Component
{
protected:
	double _health = 10;
	int coins;

public:

	explicit PlayerControlerComponent(Entity* p);
	PlayerControlerComponent() = delete;
	double getHealth();
	void setHealth(double b);
	void takeDamage(double);
	void collectCoin();
	int getCoins();
	void collisionCheck();
	void update(double dt);
	void render() override;

};