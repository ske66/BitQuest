#pragma once

#include "ecm.h"
#include <SFML/Graphics.hpp>

class SpriteComponent : public Component {
protected:
	std::shared_ptr<sf::Sprite> _sprite;
	std::shared_ptr<sf::Texture> _texture;

public:

	sf::IntRect uvRect;

	SpriteComponent() = delete;

	void Sprite(std::string a, sf::IntRect b);

	explicit SpriteComponent(Entity* p);
	void update(double dt) override;
	void render() override;


	sf::Sprite& getSprite() const;

	template <typename... Targs> void setSprite(Targs... params) {
		_sprite.reset(new sf::Sprite(params...));
	}
};