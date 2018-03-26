#include "engine.h"
#include "gameState.h"
#include "scenes\scene_Level_1.h"
#include "scenes\scene_MainMenu.h"
#include "scenes\scene_LoadGame.h"
#include "scenes\scene_Settings.h"
#include "scenes\scene_Settings_Audio.h"
#include "scenes\scene_Settings_Gameplay.h"
#include "scenes\scene_Settings_Graphics.h"


using namespace std;

MainMenuScene menu;
LoadGameScene loadgame;
SettingsScene settings;
SettingsAudioScene settingsAudio;
SettingsGraphicsScene settingsGraphics;
SettingsGameplayScene settingsGameplay;
Level1Scene level1;

int main() {

	Engine::Start(1280, 720, "Bitquest!", &menu);
}