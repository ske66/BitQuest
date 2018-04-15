#include "cmp_UI.h"
#include "engine.h"
#include "cmp_state_machine.h"
#include "System_Renderer.h"
#include "system_resources.h"
#include "../code/Prefabs.h"
#include "cmp_text.h"
#include "../code/GameState.h"

using namespace std;
using namespace sf;

UIComponent::UIComponent(Entity* p)
	:Component(p)
{

	_player = _parent->scene->ents.find("player")[0];

	_coinCount = _parent->scene->ents.find("coinCount")[0];
	_arrowCount = _parent->scene->ents.find("arrowCount")[0];
	_hamCount = _parent->scene->ents.find("hamCount")[0];

	_texHeartUI = Resources::load<Texture>("heart.png");
	_texCoinUI = Resources::load<Texture>("spritesheets/Coin_spritesheet.png");
	_texArrowUI = Resources::load<Texture>("arrowUI.png");
	_texSwordUI = Resources::load<Texture>("SwordUI.png");
	_texBowUI = Resources::load<Texture>("BowUI.png");
	_texHamUI = Resources::load<Texture>("HamUI.png");

	heartUI = Sprite(*_texHeartUI);
	heartUI.setTextureRect(IntRect(0, 0, 240, 60));

	coinUI = Sprite(*_texCoinUI);
	coinUI.setTextureRect(IntRect(0, 0, 60, 60));

	arrowUI = Sprite(*_texArrowUI);
	arrowUI.setTextureRect(IntRect(0, 0, 60, 60));

	weaponUI = Sprite(*_texSwordUI);
	weaponUI.setTextureRect(IntRect(0, 0, 60, 60));

	hamUI = Sprite(*_texHamUI);
	hamUI.setTextureRect(IntRect(0, 0, 60, 60));

	_coinCount->get_components<TextComponent>()[0]->SetText("x0");
	_arrowCount->get_components<TextComponent>()[0]->SetText("x0");
	_hamCount->get_components<TextComponent>()[0]->SetText("X0");

}

void UIComponent::update(double dt)
{
	_parent->setPosition({
		Engine::GetWindow().getView().getCenter().x,
		Engine::GetWindow().getView().getCenter().y });


	if (Keyboard::isKeyPressed(Keyboard::Num1))
	{
		auto p = _player->get_components<AnimationComponent>()[0];
		p->Animation("spritesheets/Bob_archer_spritesheetV2.png", Vector2f(0, 120), IntRect(0, 0, 240, 240), Vector2u(8, 8));
		p->getSprite().setOrigin(p->getSprite().getGlobalBounds().width / 2, p->getSprite().getGlobalBounds().height / 2);;
		weaponUI = Sprite(*_texBowUI);
		sword = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Num2))
	{
		auto p = _player->get_components<AnimationComponent>()[0];
		_player->get_components<AnimationComponent>()[0]->Animation("spritesheets/Bob_spritesheet.png", Vector2f(0, 120), IntRect(0, 0, 240, 240), Vector2u(8, 8));
		p->getSprite().setOrigin(p->getSprite().getGlobalBounds().width / 2, p->getSprite().getGlobalBounds().height / 2);
		sword = true;
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
		_parent->getPosition().y + Engine::GetWindow().getSize().y / 2.7);

	weaponUI.setPosition(
		_parent->getPosition().x - Engine::GetWindow().getSize().x / 50,
		_parent->getPosition().y + Engine::GetWindow().getSize().y / 2.7);

	hamUI.setPosition(
		_parent->getPosition().x - Engine::GetWindow().getSize().x / 2.3,
		_parent->getPosition().y + Engine::GetWindow().getSize().y / 2.7);

	_coinCount->setPosition(Vector2f(coinUI.getPosition().x + 150, coinUI.getPosition().y + 30));

	_arrowCount->setPosition(Vector2f(arrowUI.getPosition().x + 150, arrowUI.getPosition().y + 30));

	_hamCount->setPosition(Vector2f(hamUI.getPosition().x + 150, hamUI.getPosition().y + 30));

}

void UIComponent::render()
{
	Renderer::queue(&weaponSelection);
	Renderer::queue(&heartUI);
	Renderer::queue(&coinUI);
	Renderer::queue(&arrowUI);
	Renderer::queue(&weaponUI);
	Renderer::queue(&hamUI);
}

void UIComponent::setHealthDisplay(sf::IntRect s)
{
	heartUI.setTextureRect(s);
}