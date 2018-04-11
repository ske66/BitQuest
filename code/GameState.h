#pragma once

#include "scenes\scene_Level_1.h"
#include "scenes\scene_MainMenu.h"
#include "scenes\scene_Settings.h"
#include "scenes\scene_Settings_Audio.h"
#include "scenes\scene_Settings_Gameplay.h"
#include "scenes\scene_Settings_Graphics.h"
#include "scenes\Scene_Game_Over.h"

extern MainMenuScene menu;
extern SettingsScene settings;
extern SettingsAudioScene settingsAudio;
extern SettingsGraphicsScene settingsGraphics;
extern SettingsGameplayScene settingsGameplay;
extern Level1Scene level1;
extern GameOverScene gameOver;
extern bool loadGame;