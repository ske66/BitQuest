#pragma once
#include <string>

class SaveLoad
{
public:

	static void LoadGame();
	static void SaveGame();
	static void ResetGame();
	static std::string save_file_path;

	static int positionX;
	static int positionY;
	static int health;
	static int coins;
	static int hams;
	static int arrows;
	static int playerDamage;
	static int playerMaxHealth;
};