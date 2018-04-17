#pragma once
#include <string>

class Audio
{
public:

	static void LoadAudio();
	static void SaveAudio();
	static void ResetAudio();
	static std::string save_file_path;

	static int musicVolume;
	static int sfxVolume;
};