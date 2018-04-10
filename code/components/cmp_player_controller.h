#include "ecm.h"
#include "engine.h"
#include <SFML/Window/Keyboard.hpp>
#include "cmp_player_physics.h"
#include "cmp_gavin_physics.h"
#include "cmp_animation.h"

class PlayerControlerComponent : public Component
{
protected:
	int _health = 10;
	int coins = 0;
	double damageDelay = 2;
	double totalTime = 0 ;
	bool immortal = true;

public:

	explicit PlayerControlerComponent(Entity* p);
	double playerDamage();
	sf::IntRect checkHealth();
	PlayerControlerComponent() = delete;
	double getHealth();
	void setHealth(double b);
	void takeDamage(double, double dt);
	void collectCoin();
	int getCoins();
	void collisionCheck(double dt);
	void update(double dt);
	void render() override;

};