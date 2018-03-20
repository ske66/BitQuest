#pragma once
#include <ecm.h>
#include <SFML/Graphics.hpp>
#include "System_Renderer.h"

class AnimationComponent : public Component
{
protected:
	std::shared_ptr<sf::Shape> _shape;
	sf::Texture _texture;

public:
	explicit AnimationComponent(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	AnimationComponent() = delete;

	sf::IntRect uvRect;
	sf::Texture* getTexture();
	void setTexture(sf::Texture _texture);

	void update(int row, float dt, bool faceRight);
	void render() override;

	sf::Shape &getShape() const;

	template <typename T, typename... Targs>
	void setShape(Targs... params)
	{
		_shape.reset(new T(params...));
	}

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
};