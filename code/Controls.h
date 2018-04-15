#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class Controls
{
private:
	static std::map<std::string, sf::Keyboard::Key> _keyboardLookupTable;
	static std::map<std::string, sf::Mouse::Button> _mouseLookupTable;

public:
	static void initialise();
	static sf::Keyboard::Key GetKeyboardButton(std::string action);
	static sf::Mouse::Button GetMouseButton(std::string action);
	static void SetKeyboardButton(std::string action, sf::Keyboard::Key key);
	static void SetMouseButton(std::string action, sf::Mouse::Button button);
};