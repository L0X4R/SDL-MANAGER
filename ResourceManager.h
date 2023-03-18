#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#pragma region INCLUDES
#include "VideoManager.h"
#include "AudioManager.h"

#include <iostream>;
#include <map>
#include <vector>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "config.h"

using namespace std;
#pragma endregion

class ResourceManager
{
private:
	ResourceManager();

	SDL_Renderer* GPU;

	Sint32 addGraphic(const char* file);
	Sint32 addSound(const char* file);

	vector<SDL_Texture*> texturesVector;
	map<string, Sint32> texturesMap;
	Uint32 texturesFirstSlot;

	vector<Mix_Chunk*> soundsVector;
	map<string, Sint32> soundsMap;
	Uint32 soundsFirstSlot;

	static ResourceManager* pInstance;

public:
	static ResourceManager* getInstance();

	~ResourceManager();

#pragma region TEXTURES
	Sint32 loadAndGetGraphicID(const char* file);

	SDL_Texture* getGraphicByID(Sint32 ID);

	string getGraphicPathByID(Sint32 ID);

	void getGraphicSize(Sint32 img, int& width, int& height);

	Uint16 getGraphicWidth(Sint32 img);

	Uint16 getGraphicHeight(Sint32 img);

	void removeGraphic(const char* file);
#pragma endregion

#pragma region SOUNDS
	Sint32 loadAndGetSoundID(const char* file);

	Mix_Chunk* getSoundByID(Sint32 ID);

	string getSoundPathByID(Sint32 ID);

	void removeSound(const char* file);
#pragma endregion

};
#endif
