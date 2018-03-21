#include "cmp_sprite.h"
#include <iostream>
#include <System_renderer.h>
#include <System_resources.h>

using namespace std;

SpriteComponent::SpriteComponent(Entity* p )
	: Component(p),_sprite(make_shared<sf::Sprite>()) 
{

}

void SpriteComponent::update(double dt) {
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
		currentimage.y = 6;
	}

	if (_parent->getState() == "idle" )
	{
		currentimage.y = 2;
	}

	if (_parent->getState() == "attack")
	{
		currentimage.y = 7;
		
		if (currentimage.y == 7 && currentimage.x == 7)
		{
			_parent->setState("idle");
			currentimage.x = 0;
		}
	}

	totaltime += dt;

	if (totaltime >= switchtime) //<------ switch time
	{
		totaltime -= switchtime;
		currentimage.x++;
		std::cout << totaltime << endl;

		if (currentimage.x >= imagecount.x)
		{
			currentimage.x = 0;
		}
	}

	uvRect.left = currentimage.x * uvRect.width;
	uvRect.top = currentimage.y *  uvRect.height;

	_sprite->setTextureRect(uvRect);

	//std::cout << totaltime  << endl;
	//std::cout << currentimage << endl;

	//std::cout << totaltime << endl;

}



void SpriteComponent::Initialise(std::string a,sf::Vector2f b,sf::Vector2u imagecount)
{
	_texture = Resources::get<sf::Texture>(a);
	_sprite->setTexture(*_texture);
	_sprite->setTextureRect(sf::IntRect(0, 0, 240, 240));
	_sprite->setOrigin(b);
	
	this->imagecount = imagecount;
	this->switchtime = 0.1f; 

	currentimage.x = 0;
    totaltime = 0.0f;

	uvRect.width = _texture->getSize().x / float(imagecount.x);
	uvRect.height = _texture->getSize().y / float(imagecount.y);

	
}


void SpriteComponent::render() { Renderer::queue(_sprite.get()); }




void ShapeComponent::update(double dt) {

	_shape->setPosition(_parent->getPosition());
	_shape->setRotation(_parent->getRotation());

	
}


void ShapeComponent::render() { Renderer::queue(_shape.get()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p)
	: Component(p), _shape(make_shared<sf::CircleShape>()) {}

sf::Sprite& SpriteComponent::getSprite() const { return *_sprite; }
