#pragma region INCLUDES
#include "ResourceManager.h"
#include "VideoManager.h"
#include "AudioManager.h"

#include <iostream>;
#include <map>
#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "config.h"

using namespace std;
#pragma endregion

AudioManager* AudioManager::pInstance = NULL;

AudioManager::AudioManager()
{
	LOG("CREANDO EL GESTOR DE AUDIO...");
	int exitcode = SDL_InitSubSystem(SDL_INIT_AUDIO);
	LOG("CARGANDO DISPOSITIVO DE SALIDA...");
	int exitcode2 = Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, 2, 1024);
	LOG("CREANDO CANALES DE AUDIO...");
	Mix_AllocateChannels(128);

	if (exitcode == 0 && exitcode2 == 0)
	{
		GOOD("GESTOR DE AUDIO CREADO.");
	}
	else
	{
		ERROR("NO SE HA PODIDO CREAR EL GESTOR DE AUDIO.");
		exit(1);
	}
}

AudioManager::~AudioManager()
{
}

AudioManager* AudioManager::getInstance()
{
	if (pInstance == nullptr)
		pInstance = new AudioManager();

	return pInstance;
}

int AudioManager::playSound(int channel, int soundId, bool loop)
{
	ResourceManager* rm = ResourceManager::getInstance();
	Mix_Chunk* sound = rm->getSoundByID(soundId);

	if (sound == nullptr)
	{
		ERROR("NO SE HA PODIDO REPRODUCIR EL SONIDO. NO SE HA PODIDO ENCONTRAR EL ARCHIVO.");
		return -1;
	}

	int _loop = 0;

	if (loop)
	{
		_loop = 1;
	}

	int _channel = Mix_PlayChannel(channel, sound, _loop);

	if (_channel == -1)
	{
		ERROR("NO SE HA PODIDO REPRODUCIR EL SONIDO. TODOS LOS CANALES ESTAN OCUPADOS.");
	}

	return _channel;
}

void AudioManager::stopChannel(int channel)
{
	Mix_HaltChannel(channel);
}

void AudioManager::stopAllChannels()
{
	Mix_HaltChannel(-1);
}