#include "cmp_UI.h"
#include "engine.h"
#include "System_Renderer.h"

using namespace std;
using namespace sf;

RectangleShape topBar;
RectangleShape bottomBar;


UIComponent::UIComponent(Entity* p)
	:Component(p)
{
	topBar = RectangleShape({ (float)Engine::GetWindow().getSize().x, 80.f });
	topBar.setFillColor(Color::Black);
	topBar.setOrigin(0, 0);

	bottomBar = RectangleShape({ (float)Engine::GetWindow().getSize().x, 70.f });
	bottomBar.setFillColor(Color::Black);
	topBar.setOrigin(0, 0);

}

void UIComponent::update(double dt)
{
	_parent->setPosition({
		Engine::GetWindow().getView().getCenter().x,
		Engine::GetWindow().getView().getCenter().y });

	topBar.setPosition(
		_parent->getPosition().x - Engine::GetWindow().getSize().x / 2,
		_parent->getPosition().y - Engine::GetWindow().getSize().y / 2);

	bottomBar.setPosition(
		_parent->getPosition().x - Engine::GetWindow().getSize().x / 2,
		_parent->getPosition().y + Engine::GetWindow().getSize().y / 2 - 70.f);
}

void UIComponent::render()
{
	Renderer::queue(&topBar);
	Renderer::queue(&bottomBar);
}