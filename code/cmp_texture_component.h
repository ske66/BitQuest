#pragma once
#include <ecm.h>
#include <SFML/Graphics.hpp>
#include "System_Renderer.h"

class TextureComponent : public Component
{
protected:
	 std::shared_ptr<sf::Shape> _shape;
	 sf::Texture _texture;

public:

	explicit TextureComponent(Entity *p);
	TextureComponent() = delete;
	
	sf::Texture* getTexture();
	void setTexture(sf::Texture _texture);

	void update(float dt) override;
	void render() override;

	sf::Shape &getShape() const;

	template <typename T, typename... Targs>
	void setShape(Targs... params)
	{
		_shape.reset(new T(params...));
	}

};

