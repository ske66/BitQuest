#include "ecm.h"

using namespace std;
using namespace sf;


	Entity::Entity() {}
	
	void Entity::update(float dt)
	{
		for (auto c : _components)
		{
			c->update(dt);
		}
	}

	void Entity::render()
	{
		for (auto c : _components)
		{
			c->render(); 
		}
	}

	const Vector2f& Entity::getPosition() const { return _position; }

	void Entity::setPosition(const Vector2f& _position)
	{
		Entity::_position = _position;
	}
	
	float Entity::getRotation() const { return _rotation; }

	void Entity::setRotation(float _rotation)
	{
		{Entity::_rotation = _rotation; }
	}
	

	bool Entity::isAlive() const { return _alive; }

	void Entity::setAlive(bool _alive) { Entity::_alive = _alive; }

	void Entity::setForDelete() 
	{
		_fordeletion = true;
		_alive = false;
		_visible = false;
	
	}

	bool Entity::isVisible() const { return _visible;  }

	void Entity::setVisable(bool _visible) { Entity::_visible = _visible; }


	Component::Component(Entity* const p) : _parent(p), _fordeletion(false) {}



void EntityManager::update(const float dt) {
	for (auto e : list) {
		e->update(dt);
	}
}

void EntityManager::render() 
{
	for (auto e : list) {
		e->render();
	}
}

Entity::~Entity() {}
Component::~Component() {}