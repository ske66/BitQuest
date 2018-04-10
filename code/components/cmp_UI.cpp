#include "cmp_UI.h"
#include "engine.h"
#include "System_Renderer.h"
#include "system_resources.h"
#include "cmp_text.h"

using namespace std;
using namespace sf;

RectangleShape topBar;

UIComponent::UIComponent(Entity* p)
	:Component(p)
{


	_texHeartUI = Resources::load<Texture>("heart.png");
	_texCoinUI = Resources::load<Texture>("spritesheets/Coin_spritesheet.png");

	topBar = RectangleShape({ (float)Engine::GetWindow().getSize().x, 80.f });
	topBar.setFillColor(Color::Black);
	topBar.setOrigin(0, 0);

	heartUI = Sprite(*_texHeartUI);
	heartUI.setTextureRect(IntRect(0, 0, 240, 60));

	coinUI = Sprite(*_texCoinUI);
	coinUI.setTextureRect(IntRect(0, 0, 60, 60));

}

void UIComponent::update(double dt)
{
	_parent->setPosition({
		Engine::GetWindow().getView().getCenter().x,
		Engine::GetWindow().getView().getCenter().y });
	
	topBar.setPosition(
		_parent->getPosition().x - Engine::GetWindow().getSize().x / 2,
		_parent->getPosition().y - Engine::GetWindow().getSize().y / 2);
	
	heartUI.setPosition(
		_parent->getPosition().x - Engine::GetWindow().getSize().x / 2 + 30.f,
		_parent->getPosition().y - Engine::GetWindow().getSize().y / 2 + 10.f);

	coinUI.setPosition(
		_parent->getPosition().x + Engine::GetWindow().getSize().x / 3,
		_parent->getPosition().y - Engine::GetWindow().getSize().y / 2 + 10.f);

}

void UIComponent::render()
{
	Renderer::queue(&topBar);
	Renderer::queue(&heartUI);
	Renderer::queue(&coinUI);

}

void UIComponent::setHealthDisplay(sf::IntRect s)
{
	heartUI.setTextureRect(s);
}