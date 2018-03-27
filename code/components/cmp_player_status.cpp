#include "cmp_player_status.h"


PlayerStatusComponent::PlayerStatusComponent(Entity* p)
	: Component(p) 
{


}

double PlayerStatusComponent::getHealth()
{
	return _health; 
}
void PlayerStatusComponent::setHealth(double b)
{
	_health = b; 
}
void PlayerStatusComponent::update(double dt)
{

}
void PlayerStatusComponent::render()
{

}
void PlayerStatusComponent::takeDamage(double d)
{
	_health = _health - d; 
}