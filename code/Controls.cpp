#include "Controls.h"
#include "GameState.h"
#include <stdexcept>

using namespace std;
using namespace sf;

map<std::string, Keyboard::Key> Controls::_keyboardLookupTable;
map<std::string, Mouse::Button> Controls::_mouseLookupTable;

void Controls::initialise()
{
		//If using keyboard is being used
		Controls::SetKeyboardButton("Pause", Keyboard::Escape);
		Controls::SetKeyboardButton("Enter", Keyboard::Return);
		Controls::SetKeyboardButton("MoveLeft", Keyboard::A);
		Controls::SetKeyboardButton("MoveRight", Keyboard::D);
		Controls::SetKeyboardButton("Jump", Keyboard::Space);
		Controls::SetMouseButton("Attack", Mouse::Left);
		Controls::SetKeyboardButton("Sword", Keyboard::Num1);
		Controls::SetKeyboardButton("Bow", Keyboard::Num2);
}

Keyboard::Key Controls::GetKeyboardButton(string action)
{
	auto k = _keyboardLookupTable.find(action);
	if (k != _keyboardLookupTable)
}

