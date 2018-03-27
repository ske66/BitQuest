#include "cmp_animation.h"
#include <iostream>
#include <System_renderer.h>
#include <System_resources.h>

using namespace std;

void AnimationComponent::Animation(std::string a,sf::Vector2f b, sf::Vector2u imagecount)
{
	_texture = Resources::get<sf::Texture>(a);
	_sprite->setTexture(*_texture);
	_sprite->setTextureRect(sf::IntRect(0, 0, 240, 240));
	_sprite->setOrigin(b);
	
	this->imagecount = imagecount;
	this->switchtime = 0.1f; 

	currentimage.x = 0;
    totaltime = 0.0f;

	animUvRect.width = _texture->getSize().x / float(imagecount.x);
	animUvRect.height = _texture->getSize().y / float(imagecount.y);
	
}


AnimationComponent::AnimationComponent(Entity* p)
	: Component(p), _sprite(make_shared<sf::Sprite>())
{

}

void AnimationComponent::update(double dt) {
	_sprite->setPosition(_parent->getPosition());
	_sprite->setRotation(_parent->getRotation());


	if (_parent->getState() == "walk_right")
	{
		currentimage.y = 0;
	}

	if (_parent->getState() == "walk_left")
	{
		currentimage.y = 0;
	}

	if (_parent->getState() == "jump")
	{
		currentimage.y = 2;
	}

	if (_parent->getState() == "idle")
	{
		currentimage.y = 2;
	}

	if (_parent->getState() == "attack")
	{
		currentimage.y = 7;

		std::cout << currentimage.x << endl;

		if (currentimage.y == 7 && currentimage.x == 7)
		{
			_parent->setState("idle");
		}
	}

	totaltime += dt;

	if (totaltime >= switchtime) 
	{
		totaltime -= switchtime;
		currentimage.x++;

		if (currentimage.x >= imagecount.x)
		{
			currentimage.x = 0;
		}
	}

	animUvRect.left = currentimage.x * animUvRect.width;
	animUvRect.top = currentimage.y *  animUvRect.height;


	_sprite->setTextureRect(animUvRect);
}

void AnimationComponent::render() { Renderer::queue(_sprite.get()); }




void ShapeComponent::update(double dt) {

	_shape->setPosition(_parent->getPosition());
	_shape->setRotation(_parent->getRotation());

	
}


void ShapeComponent::render() { Renderer::queue(_shape.get()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p)
	: Component(p), _shape(make_shared<sf::CircleShape>()) {}

sf::Sprite& AnimationComponent::getSprite() const { return *_sprite; }
