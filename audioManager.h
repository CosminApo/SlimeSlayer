#ifndef _AUDIO_MANAGER_H
#define _AUDIO_MANAGER_H
#include "SDL_mixer.h"
#include <string>
#include <iostream>
class audioManager
{
	Mix_Music* bgm;
	Mix_Chunk* sfx;
public:
	void setBgm(std::string _path);
	void setSfx(std::string _path);
	void play();
	void stopMusic();
	void resumeMusic();

	audioManager();
	~audioManager();
};

#endif //! _AUDIO_MANAGER_H