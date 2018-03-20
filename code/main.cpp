#include "engine.h"
#include "gameState.h"
#include "scenes\scene_MainMenu.h"

using namespace std;

MainMenuScene menu;
Level1Scene level1;

int main() {

	Engine::Start(1280, 720, "Bitquest!", &menu);
}