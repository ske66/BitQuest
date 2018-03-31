#include "cmp_btn.h"
#include "engine.h"
#include <SFML/Window/Mouse.hpp>

using namespace std;
using namespace sf;

BtnComponent::BtnComponent(Entity* p, shared_ptr<ShapeComponent> s, shared_ptr<TextComponent> t, shared_ptr<ShapeComponent> u)
	: _shapeCmp(s), _textCmp(t), _underLine(u), Component(p)
{
	setHighlighted(false, true);
}

void BtnComponent::update(double dt)
{
	auto mousePos = Engine::GetWindow().mapPixelToCoords(Mouse::getPosition(Engine::GetWindow()));
	if (_shapeCmp->getShape().getGlobalBounds().contains(mousePos))
	{
		setHighlighted(true);
	}
	else
	{
		setHighlighted(false);
	}
}

void BtnComponent::setHighlighted(bool h, bool isClicked)
{
	if (h != _isHighlighted || isClicked)
	{
		_isHighlighted = h;
		if (h)
		{
			_textCmp->getText().setFillColor(Color(240, 178, 0));
			_underLine->getShape().setFillColor(Color(240, 178, 0));
		}
		else
		{
			_textCmp->getText().setFillColor(Color(255,255,255));
			_underLine->getShape().setFillColor(Color(128,128,128));
		}
	}
}

bool BtnComponent::isSelected()
{
	if (_isHighlighted)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			return true;
		}
	}
	return false;
}