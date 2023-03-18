#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#pragma region INCLUDES
#include "ResourceManager.h"
#include "AudioManager.h"

#include <iostream>
#include <map>
#include <vector>

#include "SDL_mixer.h"
#include "config.h"

using namespace std;
#pragma endregion

class AudioManager
{
private:
	AudioManager();
	static AudioManager* pInstance;

public:
	static AudioManager* getInstance();
	~AudioManager();

	int playSound(int channel, int soundId, bool loop = false);

	void stopChannel(int channel);

	void stopAllChannels();
};
#endif // !AUDIOMANAGER_H

