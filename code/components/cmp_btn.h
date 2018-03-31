#pragma once

#include <ecm.h>
#include "cmp_text.h"
#include "cmp_animation.h"

class BtnComponent : public Component
{
private:
	bool _isHighlighted = false;
	std::shared_ptr<ShapeComponent> _shapeCmp;
	std::shared_ptr<TextComponent> _textCmp;
	std::shared_ptr<ShapeComponent> _underLine;

public:
	BtnComponent() = delete;
	explicit BtnComponent(Entity* p, std::shared_ptr<ShapeComponent>, std::shared_ptr<TextComponent>, std::shared_ptr<ShapeComponent>);
	void update(double dt) override;
	void render() override {}
	void setHighlighted(bool, bool isClicked = false);
	bool isSelected();

};