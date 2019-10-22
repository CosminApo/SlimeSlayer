#include "audioManager.h"



void audioManager::setBgm(std::string _path)
{
	bgm = Mix_LoadMUS(_path.c_str());
	if (bgm == nullptr)
	{
		std::cout << "Could not load music file: " << _path << std::endl;
	}
}

void audioManager::setSfx(std::string _path)
{
	sfx = Mix_LoadWAV(_path.c_str());

	if (sfx == nullptr)
	{
		std::cout << "Could not load sfx file: " << _path << std::endl;
	}

}

void audioManager::play()
{
	if (bgm != nullptr && !Mix_PlayingMusic()) //if there is a bgm loaded and its not currently playing
	{
		Mix_VolumeMusic(10); //0 to 128
		Mix_FadeInMusic(bgm, -1, 3000); //play on a loop, start with a fade effect
	}
	if (sfx != nullptr)
	{
		Mix_Volume(-1, 5); //0 to 128
		Mix_PlayChannel(-1, sfx, 0);
	}
}

void audioManager::stopMusic()
{
	Mix_FreeMusic(bgm);
}

void audioManager::resumeMusic()
{
	Mix_ResumeMusic();
}


audioManager::audioManager()
{
	sfx = nullptr;
	bgm = nullptr;
}


audioManager::~audioManager()
{
	bgm = nullptr;
	sfx = nullptr;
}
