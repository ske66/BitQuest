#pragma once
#include "cmp_state.h"
#include "ecm.h"
#include "engine.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <System_renderer.h>
#include <System_resources.h>


class AnimationComponent : public Component {
protected:
	std::shared_ptr<sf::Sprite> _sprite;
	std::shared_ptr<sf::Texture> _texture;

public:

	double switchtime;
	sf::IntRect animUvRect;
	sf::Vector2u currentimage;
	double totaltime;
	sf::Vector2u imagecount;
	int attackImgNo;
	bool animDone;

	void Anim(double dt);
	void attackAnim(double dt);

	AnimationComponent() = delete;

	void Animation(std::string a, sf::Vector2f b, sf::IntRect animUvRect, sf::Vector2u imagecount);


	explicit AnimationComponent(Entity* p);
	void update(double dt);
	void render() override;

	sf::Sprite& getSprite() const;

	template <typename... Targs> void setSprite(Targs... params) {
		_sprite.reset(new sf::Sprite(params...));
	}

};

class ShapeComponent : public Component {
protected:
	std::shared_ptr<sf::Shape> _shape;

public:
	ShapeComponent() = delete;

	explicit ShapeComponent(Entity* p);

	void update(double dt) override;
	void render() override;
	sf::Shape& getShape() const;
	template <typename T, typename... Targs> void setShape(Targs... params) {
		_shape.reset(new T(params...));
	}
};