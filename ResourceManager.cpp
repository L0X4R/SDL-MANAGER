#pragma region INCLUDES
#include "ResourceManager.h"
#pragma endregion

ResourceManager* ResourceManager::pInstance = NULL;

ResourceManager::ResourceManager()
{
	LOG("CREANDO EL GESTOR DE RECURSOS...");
	VideoManager* WINDOW = VideoManager::getInstance();
	GPU = WINDOW->GPU;

	LOG("INICIANDO SDL IMAGE...");
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);

	texturesFirstSlot = -1;
	soundsFirstSlot = -1;

	if ((initted & flags) != flags)
	{
		ERROR("NO SE HA PODIDO INICIAR EL SDL IMAGE.");
		cout << IMG_GetError();
		exit(1);
	}
	else
	{
		GOOD("GESTOR DE RECURSOS CREADO.");
	}
}

ResourceManager::~ResourceManager()
{
}

ResourceManager* ResourceManager::getInstance()
{
	if (pInstance == nullptr)
	{
		pInstance = new ResourceManager();
	}

	return pInstance;
}

#pragma region TEXTURES
Sint32 ResourceManager::loadAndGetGraphicID(const char* file)
{
	map<string, Sint32>::iterator it;

	if (!file || file == "")
	{
		ERROR("PATHFILE EMPTY.");
		return -1;
	}

	LOG("SEARCHING GRAPHIC...");
	it = texturesMap.find(file);

	if (it != texturesMap.end())
	{
		LOG("GRAPHIC ALREDY EXISTS. | ID: " << it->second);
		return it->second;
	}
	else
	{
		LOG("GRAPHIC NOT FOUND.");
		return addGraphic(file);
	}
}

SDL_Texture* ResourceManager::getGraphicByID(Sint32 ID)
{
	map<string, Sint32>::iterator it;

	for (it = texturesMap.begin(); it != texturesMap.end(); ++it)
	{
		if (it->second == ID)
		{
			return texturesVector[ID];
		}
	}

	ERROR("GRAPHIC NOT FOUND.");

	return nullptr;
}

string ResourceManager::getGraphicPathByID(Sint32 ID)
{
	map<string, Sint32>::iterator it;

	string filepath = "";

	for (it = texturesMap.begin(); it != texturesMap.end(); ++it)
	{
		if (it->second == ID)
		{
			filepath = it->first;
		}
	}

	return filepath;
}

Sint32 ResourceManager::addGraphic(const char* file)
{
	SDL_Texture* tempTexture = IMG_LoadTexture(GPU, file);

	if (tempTexture == NULL)
	{
		ERROR("GRAPHIC PATHFILE NOT FOUND.");
		exit(1);
	}

	if (texturesFirstSlot != -1)
	{
		texturesVector[texturesFirstSlot] = tempTexture;
		texturesMap.insert({ file, texturesFirstSlot });
		ADD("NEW GRAPHIC | ID: " << texturesFirstSlot);
		return texturesFirstSlot;
	}
	else
	{
		texturesVector.push_back(tempTexture);
		int last = texturesVector.size();
		last = last - 1;
		texturesMap.insert({ file, last });
		ADD("NEW GRAPHIC | ID: " << last);
		return last;
	}
}

void ResourceManager::getGraphicSize(Sint32 img, int& width, int& height)
{
	map<string, Sint32>::iterator it;

	for (it = texturesMap.begin(); it != texturesMap.end(); ++it)
	{
		if (it->second == img)
		{
			SDL_Point size;
			SDL_QueryTexture(texturesVector[img], NULL, NULL, &size.x, &size.y);
			width = size.x;
			height = size.y;
			break;
		}
	}
}

Uint16 ResourceManager::getGraphicWidth(Sint32 img)
{
	map<string, Sint32>::iterator it;

	for (it = texturesMap.begin(); it != texturesMap.end(); ++it)
	{
		if (it->second == img)
		{
			SDL_Point size;
			SDL_QueryTexture(texturesVector[img], NULL, NULL, &size.x, &size.y);
			return size.x;
			break;
		}
	}

	return NULL;
}

Uint16 ResourceManager::getGraphicHeight(Sint32 img)
{
	map<string, Sint32>::iterator it;

	for (it = texturesMap.begin(); it != texturesMap.end(); ++it)
	{
		if (it->second == img)
		{
			SDL_Point size;
			SDL_QueryTexture(texturesVector[img], NULL, NULL, &size.x, &size.y);
			return size.y;
			break;
		}
	}

	return NULL;
}

void ResourceManager::removeGraphic(const char* file)
{
	if (texturesMap.find(file) == texturesMap.end())
	{
		ERROR("GRAPHIC NOT FOUND, CAN'T REMOVE.");
	}
	else
	{
		map<string, Sint32>::iterator it;

		for (it = texturesMap.begin(); it != texturesMap.end(); ++it)
		{
			if (it->first == file)
			{
				string filepath = it->first;
				int fileID = it->second;

				SDL_DestroyTexture(texturesVector[fileID]);

				texturesVector[fileID] = NULL;

				texturesMap.erase(it);
				DEL("ID: " << fileID << " | " << filepath);
				break;
			}
		}

		for (int i = 0; i < texturesVector.size(); i++)
		{
			if (texturesVector[i] == NULL)
			{
				texturesFirstSlot = i;
				break;
			}
		}
	}
}
#pragma endregion

#pragma region SOUNDS
Sint32 ResourceManager::loadAndGetSoundID(const char* file)
{
	map<string, Sint32>::iterator it;

	if (!file || file == "")
	{
		ERROR("PATHFILE EMPTY.");
		return -1;
	}

	LOG("SEARCHING AUDIO...");
	it = soundsMap.find(file);

	if (it != soundsMap.end())
	{
		LOG("AUDIO ALREDY EXISTS. | ID: " << it->second);
		return it->second;
	}
	else
	{
		LOG("AUDIO NOT FOUND.");
		return addSound(file);
	}
}

Mix_Chunk* ResourceManager::getSoundByID(Sint32 ID)
{
	map<string, Sint32>::iterator it;

	for (it = soundsMap.begin(); it != soundsMap.end(); ++it)
	{
		if (it->second == ID)
		{
			return soundsVector[ID];
		}
	}

	ERROR("SOUND NOT FOUND.");

	return nullptr;
}

string ResourceManager::getSoundPathByID(Sint32 ID)
{
	map<string, Sint32>::iterator it;

	string filepath = "";

	for (it = soundsMap.begin(); it != soundsMap.end(); ++it)
	{
		if (it->second == ID)
		{
			filepath = it->first;
			break;
		}
	}

	return filepath;
}


Sint32 ResourceManager::addSound(const char* file)
{
	Mix_Chunk* tempSound = Mix_LoadWAV(file);

	if (soundsFirstSlot != -1)
	{
		soundsVector[soundsFirstSlot] = tempSound;
		soundsMap.insert({ file, soundsFirstSlot });
		ADD("NEW SOUND | ID: " << soundsFirstSlot);
		return soundsFirstSlot;
	}
	else
	{
		soundsVector.push_back(tempSound);
		int last = soundsVector.size();
		last = last - 1;
		soundsMap.insert({ file, last });
		ADD("NEW SOUND | ID: " << last);
		return last;
	}
}

void ResourceManager::removeSound(const char* file)
{
	if (soundsMap.find(file) == soundsMap.end())
	{
		ERROR("SOUND NOT FOUND, CAN'T REMOVE.");
	}
	else
	{
		map<string, Sint32>::iterator it;

		for (it = soundsMap.begin(); it != soundsMap.end(); ++it)
		{
			if (it->first == file)
			{
				string filepath = it->first;
				int fileID = it->second;

				Mix_FreeChunk(soundsVector[fileID]);

				soundsVector[fileID] = NULL;

				soundsMap.erase(it);
				DEL("ID: " << fileID << " | " << filepath);
				break;
			}
		}

		for (int i = 0; i < soundsVector.size(); i++)
		{
			if (soundsVector[i] == NULL)
			{
				soundsFirstSlot = i;
				break;
			}
		}
	}
}
#pragma endregion