#include "Prefabs.h"
#include "engine.h"
#include <levelsystem.h>
#include <system_resources.h>

#include "components\cmp_btn.h"

using namespace std;
using namespace sf;

shared_ptr<Entity> makeButton(string text, Vector2f bounds)
{

	auto button = Engine::GetActiveScene()->makeEntity();
	button->addTag("button");

	auto s = button->addComponent<ShapeComponent>();
	s->setShape<RectangleShape>(Vector2f(bounds));
	s->getShape().setFillColor(Color::Transparent);
	s->getShape().setOrigin(s->getShape().getGlobalBounds().width / 2, s->getShape().getGlobalBounds().height / 2);

	auto u = button->addComponent<ShapeComponent>();
	u->setShape<RectangleShape>(Vector2f(bounds.x, 5.f));
	u->getShape().setFillColor(Color(128,128,128));
	u->getShape().setOrigin(u->getShape().getGlobalBounds().width / 2, u->getShape().getGlobalBounds().height / 2 - 30);
	
	auto t = button->addComponent<TextComponent>(text);
	t->getText().setOrigin(t->getText().getGlobalBounds().width / 2, t->getText().getGlobalBounds().height / 2);

	button->addComponent<BtnComponent>(s, t, u);

	return button;
}