#include "SaveLoad.h"
#include <fstream>

using namespace std;

int SaveLoad::positionX;
int SaveLoad::positionY;
int SaveLoad::health;
int SaveLoad::coins;
int SaveLoad::hams;
int SaveLoad::arrows;
int SaveLoad::playerDamage;
int SaveLoad::playerMaxHealth;

string SaveLoad::save_file_path = "res/savestates/PlayerProperties.txt";

void SaveLoad::LoadGame()
{
	ifstream file(save_file_path);
	if (file.good())
	{
		file >> positionX;
		file >> positionY; 
		file >> health; 
		file >> coins;
		file >> hams;
		file >> arrows;
		file >> playerDamage;
		file >> playerMaxHealth;
	}
}

void SaveLoad::SaveGame()
{
	printf("Opening save file...\n");
	ofstream file;
	file.open(save_file_path, ofstream::trunc);

	printf("Saving...\n");
	file <<
				(int)positionX << " " <<
				(int)positionY << " " <<
				(int)health << " " <<
				(int)coins << " " <<
				(int)hams << " " <<
				(int)arrows << " " <<
				(int)playerDamage << " " <<
				(int)playerMaxHealth;

	printf("Closing save file...\n");
	file.close();
}

void SaveLoad::ResetGame()
{
	positionX = 1200;
	positionY = 15360;
	health = 5;
	coins = 0;
	hams = 0;
	arrows = 10;
	playerDamage = 1;
	playerMaxHealth = 5;
}