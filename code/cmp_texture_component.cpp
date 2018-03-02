#include "cmp_texture_component.h"



TextureComponent::TextureComponent(Entity *p) : Component(p) {};



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



