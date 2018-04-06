#include "engine.h"
#include "gameState.h"
#include "scenes\scene_Level_1.h"
#include "scenes\scene_MainMenu.h"
#include "scenes\scene_LoadGame.h"
#include "scenes\scene_Settings.h"
#include "scenes\scene_Settings_Audio.h"
#include "scenes\scene_Settings_Gameplay.h"
#include "scenes\scene_Settings_Graphics.h"
#include <SFML/Window/VideoMode.hpp>
#include <SFML\Graphics.hpp>
#include <fstream>
#include <iostream>


using namespace std;

//List of all scenes
MainMenuScene menu;
LoadGameScene loadgame;
SettingsScene settings;
SettingsAudioScene settingsAudio;
SettingsGraphicsScene settingsGraphics;
SettingsGameplayScene settingsGameplay;
Level1Scene level1;

int ResolutionX;
int ResolutionY;
int FPS;



int main() {

	ifstream Graphics("res/savestates/Graphics.txt");
	(Graphics >> ResolutionX >> ResolutionY >> FPS);

	Engine::Start(ResolutionX, ResolutionY, "Bitquest!", &menu);

	}