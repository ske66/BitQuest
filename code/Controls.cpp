#include "Controls.h"
#include "GameState.h"
#include <stdexcept>

using namespace std;
using namespace sf;

map<std::string, Keyboard::Key> Controls::_keyboardLookupTable;

void Controls::initialise()
{
		//If using keyboard is being used
		Controls::SetKeyboardButton("Action", Keyboard::Return);
		Controls::SetKeyboardButton("MoveLeft", Keyboard::A);
		Controls::SetKeyboardButton("MoveRight", Keyboard::D);
		Controls::SetKeyboardButton("Jump", Keyboard::Space);
		Controls::SetKeyboardButton("Attack",Keyboard::L);
		Controls::SetKeyboardButton("Block", Keyboard::K);
		Controls::SetKeyboardButton("Sword", Keyboard::Num1);
		Controls::SetKeyboardButton("Bow", Keyboard::Num2);
}

Keyboard::Key Controls::GetKeyboardButton(string action)
{
	auto k = _keyboardLookupTable.find(action);
	if (k != _keyboardLookupTable.end())
	{
		return k->second;
	}
	else
	{
		throw invalid_argument("Action not known");
	}
}

void Controls::SetKeyboardButton(string action, Keyboard::Key key)
{
	_keyboardLookupTable[action] = key;
}


