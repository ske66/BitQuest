#include "cmp_animation_component.h"


/*

AnimationComponent::AnimationComponent(std::string path, sf::Vector2u imageCount, float switchTime) : Component(p) 
{


	imageCount = imageCount;
	switchTime = switchTime;
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

*/


