#include "cmp_UI.h"
#include "engine.h"
#include "System_Renderer.h"
#include "system_resources.h"
#include "../code/Prefabs.h"
#include "cmp_text.h"

using namespace std;
using namespace sf;

RectangleShape topBar;

UIComponent::UIComponent(Entity* p)
	:Component(p)
{



	_coinCount = _parent->scene->ents.find("coinCount")[0];
	_arrowCount = _parent->scene->ents.find("arrowCount")[0];

	_texHeartUI = Resources::load<Texture>("heart.png");
	_texCoinUI = Resources::load<Texture>("spritesheets/Coin_spritesheet.png");
	_texArrowUI = Resources::load<Texture>("arrowUI.png");
	_texSwordUI = Resources::load<Texture>("SwordUI.png");
	_texBowUI = Resources::load<Texture>("BowUI.png");

	weaponSelection = RectangleShape(Vector2f(65, 65));
	weaponSelection.setFillColor(Color(255, 255, 255, 20));
	weaponSelection.setOutlineColor(Color(240, 178, 0));
	weaponSelection.setOutlineThickness(3.f);

	heartUI = Sprite(*_texHeartUI);
	heartUI.setTextureRect(IntRect(0, 0, 240, 60));

	coinUI = Sprite(*_texCoinUI);
	coinUI.setTextureRect(IntRect(0, 0, 60, 60));

	arrowUI = Sprite(*_texArrowUI);
	arrowUI.setTextureRect(IntRect(0, 0, 100, 100));

	weaponUI = Sprite(*_texSwordUI);
	weaponUI.setTextureRect(IntRect(0, 0, 100, 100));
	
	_coinCount->get_components<TextComponent>()[0]->SetText("x0");
	_arrowCount->get_components<TextComponent>()[0]->SetText("x0");
}

void UIComponent::update(double dt)
{
	_parent->setPosition({
		Engine::GetWindow().getView().getCenter().x,
		Engine::GetWindow().getView().getCenter().y });


	if (Keyboard::isKeyPressed(Keyboard::Num2))
	{
		weaponUI = Sprite(*_texBowUI);

	}
	if (Keyboard::isKeyPressed(Keyboard::Num1))
	{
		weaponUI = Sprite(*_texSwordUI);
	}
	

	heartUI.setPosition(
		_parent->getPosition().x - Engine::GetWindow().getSize().x / 2 + 30.f,
		_parent->getPosition().y - Engine::GetWindow().getSize().y / 2 + 10.f);

	coinUI.setPosition(
		_parent->getPosition().x + Engine::GetWindow().getSize().x / 3,
		_parent->getPosition().y - Engine::GetWindow().getSize().y / 2 + 10.f);

	arrowUI.setPosition(
		_parent->getPosition().x + Engine::GetWindow().getSize().x / 3,
		_parent->getPosition().y - Engine::GetWindow().getSize().y / 2 * (-0.8));

	_coinCount->setPosition(Vector2f(_parent->getPosition().x + Engine::GetWindow().getSize().x / 3 * 1.65,
		_parent->getPosition().y - Engine::GetWindow().getSize().y / 2 * 0.95 ));

	_arrowCount->setPosition(Vector2f(_parent->getPosition().x + Engine::GetWindow().getSize().x / 3 * 1.65,
		_parent->getPosition().y - Engine::GetWindow().getSize().y / 2 * (-0.86)));


	weaponUI.setPosition(
		_parent->getPosition().x + Engine::GetWindow().getSize().x * (-0.4),
		_parent->getPosition().y - Engine::GetWindow().getSize().y / 2 * (-0.8));

	
}

void UIComponent::render()
{
	Renderer::queue(&weaponSelection);
	Renderer::queue(&heartUI);
	Renderer::queue(&coinUI);
	Renderer::queue(&arrowUI);
	Renderer::queue(&weaponUI);
}

void UIComponent::setHealthDisplay(sf::IntRect s)
{
	heartUI.setTextureRect(s);
}