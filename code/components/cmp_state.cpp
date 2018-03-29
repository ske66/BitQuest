#include "cmp_state.h"

StateComponent::StateComponent(Entity* p)
	: Component(p)
{}


bool StateComponent::getWalkingLeft()
{
	return isWalkingLeft;
}
bool StateComponent::getWalkingRight()
{
	return isWalkingRight;
}
bool StateComponent::getAttacking()
{
	return isAttacking;
}
bool StateComponent::getJumping()
{
	return isJumping;
}
bool StateComponent::getIdle()
{
	return isIdle;
}

void StateComponent::setWalkingLeft()
{
	isWalkingLeft = true;
	isWalkingRight = false;
	isJumping = false;
	isAttacking = false;
	isIdle = false;
}
void StateComponent::setWalkingRight()
{
	isWalkingLeft = false;
	isWalkingRight = true;
	isJumping = false;
	isAttacking = false;
	isIdle = false;
}
void StateComponent::setJumping()
{
	isWalkingLeft = false;
	isWalkingRight = false;
	isJumping = true;
	isAttacking = false;
	isIdle = false;
}
void StateComponent::setAttacking()
{
	isWalkingLeft = false;
	isWalkingRight = false;
	isJumping = false;
	isAttacking = true;
	isIdle = false;
}
void StateComponent::setIdle()
{
	isWalkingLeft = false;
	isWalkingRight = false;
	isJumping = false;
	isAttacking = false;
	isIdle = true;
}

void StateComponent::update(double dt)
{

}
void StateComponent::render()
{

}
