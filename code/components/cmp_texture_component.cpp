#include "cmp_texture_component.h"



TextureComponent::TextureComponent(Entity *p) : Component(p) {};



void TextureComponent::update(double dt)
{
	_shape->setPosition(_parent->getPosition());
}

void TextureComponent::render()
{
	Renderer::queue(_shape.get());
}

void TextureComponent::setTexture(sf::Texture _texture)
{
	{TextureComponent::_texture = _texture; }
}

sf::Texture* TextureComponent::getTexture()
{
	return &_texture;
}

sf::Shape& TextureComponent::getShape() const { return *_shape; }



