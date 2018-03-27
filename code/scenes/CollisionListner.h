#pragma once
#include "Box2D\Box2D.h"

class Mylistener : public b2ContactListener
{
	void BeginContact(b2Contact* contact);
	
	void EndContact(b2Contact* contact);
	
};
