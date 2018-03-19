#include "cmp_animation_component.h"


AnimationComponent::AnimationComponent(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) : Component(p) 
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);

};


void AnimationComponent::update(int row, float dt, bool faceRight)
{
	currentImage.y = row;
	totalTime += dt;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	uvRect.top = currentImage.x * uvRect.width;

	if (faceRight)
	{
		uvRect.left = currentImage.y * uvRect.height;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}





	void TextureComponent::update(float dt)
	{
		_shape->setPosition(_parent->getPosition());
	}

	void TextureComponent::render()
	{
		Renderer::queue(_shape.get());
	}

	sf::Texture* TextureComponent::getTexture()
	{
		return &_texture;
	}

	void TextureComponent::setTexture(sf::Texture _texture)
	{
		{TextureComponent::_texture = _texture; }
	}


	sf::Shape& TextureComponent::getShape() const { return *_shape; }



