#include "CollisionListner.h"
#include <iostream>
#include <string>


	void  Mylistener::BeginContact(b2Contact* contact)
	{

		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();
		b2Body* body1 = fixtureA->GetBody();
		b2Body* body2 = fixtureB->GetBody();
		
		std::cout << body1->GetUserData() << std::endl;

	}
	void Mylistener::EndContact(b2Contact* contact)
	{
		std::cout << "ended\n" << std::endl;
	}

