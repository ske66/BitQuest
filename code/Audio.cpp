#include "Audio.h"
#include <fstream>

using namespace std;

int Audio::musicVolume;
int Audio::sfxVolume;

string Audio::save_file_path = "res/savestates/Audio.txt";

void Audio::LoadAudio()
{
	ifstream file(save_file_path);
	if (file.good())
	{
		file >> musicVolume;
		file >> sfxVolume;
	}
}

void Audio::SaveAudio()
{
	printf("Opening save file...\n");
	ofstream file;
	file.open(save_file_path, ofstream::trunc);

	printf("Saving...\n");
	file <<
				(int)musicVolume << " " <<
				(int)sfxVolume;

	printf("Closing save file...\n");
	file.close();
}

void Audio::ResetAudio()
{
	musicVolume = 50;
	sfxVolume = 50;
}