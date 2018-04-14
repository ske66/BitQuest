#include "ecm.h"
#include "engine.h"
#include <SFML/Window/Keyboard.hpp>
#include "cmp_player_physics.h"
#include "cmp_gavin_physics.h"
#include "cmp_animation.h"
#include <SFML\Audio.hpp>

class PlayerControlerComponent : public Component
{
protected:
	float _health = 10;
	int coins = 0;
	double damageDelay = 2;
	double totalTime = 0 ;
	sf::SoundBuffer _bufferHit;
	sf::SoundBuffer _bufferDeath;
	sf::Sound _soundHit;
	sf::Sound _soundDeath;
	std::shared_ptr<Entity> _gavin;
	
public:
	
	bool sword = false;
	explicit PlayerControlerComponent(Entity* p);
	double playerDamage;
	bool immortal = true;
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