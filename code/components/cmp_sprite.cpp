#include "cmp_sprite.h"
#include <iostream>
#include <System_renderer.h>
#include <System_resources.h>

using namespace std;

void SpriteComponent::Sprite(std::string a, sf::IntRect uvRect)
{
	_texture = Resources::get<sf::Texture>(a);
	_sprite->setTexture(*_texture);
	_sprite->setTextureRect(uvRect);
	_sprite->setOrigin(120, 120);

	this->uvRect = uvRect;
}

SpriteComponent::SpriteComponent(Entity* p)
	: Component(p), _sprite(make_shared<sf::Sprite>())
{

}

void SpriteComponent::update(double dt) {
	_sprite->setPosition(_parent->getPosition());
	_sprite->setRotation(_parent->getRotation());

	_sprite->setTextureRect(uvRect);
}

void SpriteComponent::render() { Renderer::queue(_sprite.get()); }

//void ShapeComponent::update(double dt) {

	//_shape->setPosition(_parent->getPosition());
	//_shape->setRotation(_parent->getRotation());
//}

//void ShapeComponent::render() { Renderer::queue(_shape.get()); }

//sf::Shape& ShapeComponent::getShape() const { return *_shape; }

//ShapeComponent::ShapeComponent(Entity* p)
//	: Component(p), _shape(make_shared<sf::CircleShape>()) {}

//sf::Sprite& SpriteComponent::getSprite() const { return *_sprite; }