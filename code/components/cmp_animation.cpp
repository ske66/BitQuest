#include "cmp_animation.h"

using namespace std;

void AnimationComponent::Animation(std::string a, sf::Vector2f b, sf::IntRect animUvRect, sf::Vector2u imagecount)
{
	_texture = Resources::get<sf::Texture>(a);
	_sprite->setTexture(*_texture);
	_sprite->setTextureRect(animUvRect);
	_sprite->setOrigin(b);

	this->imagecount = imagecount;
	this->animUvRect = animUvRect;
	this->switchtime = 0.1f;

	attackImgNo = 0;
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



	auto c = _parent->get_components<StateComponent>()[0];


	if (c->getAttacking() == true)
	{
		currentimage.y = 7;
		attackAnim(dt);

		if (attackImgNo == 7)
		{
			c->setIdle();
			attackImgNo = 0;
		}
	}
	else if (c->getWalkingRight() == true )
	{
		if (attackImgNo != 0)
		{
			c->setAttacking();
		}
		else
		{
			faceRight = true;
			currentimage.y = 0;
			Anim(dt);
		}

	}
	else if (c->getWalkingLeft() == true)
	{
		if (attackImgNo != 0)
		{
			c->setAttacking();
		}
		else
		{
			faceRight = false;
			currentimage.y = 0;
			Anim(dt);
		}

	}
	else if (c->getJumping() == true || c->getIdle() == true)
	{
		if (attackImgNo != 0)
		{
			c->setAttacking();
		}
		else
		{
			currentimage.y = 2;
			Anim(dt);
		}
	}

	else if (c->getAttacking() == true)
	{
		currentimage.y = 7;
		attackAnim(dt);

		if (attackImgNo == 7)
		{
			c->setIdle();
			attackImgNo = 0;
		}
	}
	else
	{
		Anim(dt);
	}


}

void AnimationComponent::render() { Renderer::queue(_sprite.get()); }

void AnimationComponent::Anim(double dt)
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


	if (faceRight)
	{
		animUvRect.left = currentimage.x * animUvRect.width;
		animUvRect.width = abs(animUvRect.width);
	}
	else
	{
		animUvRect.left = (currentimage.x + 1) * abs(animUvRect.width);
		animUvRect.width = -abs(animUvRect.width);
	}



	_sprite->setTextureRect(animUvRect);

}

void AnimationComponent::attackAnim(double dt)
{
	totaltime += dt;


	if (totaltime >= switchtime)
	{
		totaltime -= switchtime;
		attackImgNo++;

		if (attackImgNo >= imagecount.x)
		{
			attackImgNo = 0;
		}
	}

	
	animUvRect.top = currentimage.y *  animUvRect.height;

	if (faceRight)
	{
		animUvRect.left = attackImgNo * animUvRect.width;
		animUvRect.width = abs(animUvRect.width);
	}
	else
	{
		animUvRect.left = (attackImgNo + 1) * abs(animUvRect.width);
		animUvRect.width = -abs(animUvRect.width);
	}


	_sprite->setTextureRect(animUvRect);

}

void ShapeComponent::update(double dt) {

	_shape->setPosition(_parent->getPosition());
	_shape->setRotation(_parent->getRotation());


}


void ShapeComponent::render() { Renderer::queue(_shape.get()); }

sf::Shape& ShapeComponent::getShape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p)
	: Component(p), _shape(make_shared<sf::CircleShape>()) {}

sf::Sprite& AnimationComponent::getSprite() const { return *_sprite; }