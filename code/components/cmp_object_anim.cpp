#include "cmp_object_anim.h"

using namespace std;

void ObjectAnimComponent::Animation(std::string a, sf::Vector2f b, sf::IntRect animUvRect, sf::Vector2u imagecount)
{
	_texture = Resources::get<sf::Texture>(a);
	_sprite->setTexture(*_texture);
	_sprite->setTextureRect(animUvRect);
	_sprite->setOrigin(b);

	this->imagecount = imagecount;
	this->animUvRect = animUvRect;
	this->switchtime = 0.1f;

	currentimage.x = 0;
	totaltime = 0.0f;

	animUvRect.width = _texture->getSize().x / (imagecount.x);
	animUvRect.height = _texture->getSize().y / (imagecount.y);
}

ObjectAnimComponent::ObjectAnimComponent(Entity* p)
	: Component(p), _sprite(make_shared<sf::Sprite>())
{

}

void ObjectAnimComponent::update(double dt) {

	_sprite->setPosition(_parent->getPosition());
	_sprite->setRotation(_parent->getRotation());

	Anim(dt);

}

void ObjectAnimComponent::render() { Renderer::queue(_sprite.get()); }

void ObjectAnimComponent::Anim(double dt)
{

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


	animUvRect.top = currentimage.y *  animUvRect.height;


	animUvRect.left = (currentimage.x + 1) * abs(animUvRect.width);
	animUvRect.width = -abs(animUvRect.width);



	_sprite->setTextureRect(animUvRect);

}




sf::Sprite& ObjectAnimComponent::getSprite() const { return *_sprite; }