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

VideoManager* VideoManager::pInstance = NULL;

VideoManager::VideoManager()
{
	LOG("CREANDO EL GESTOR DE VIDEO...");
	gWindow = NULL;
	GPU = NULL;

	lastTime = 0;
	currentTime = 0;
	deltaTime = 0;

	int exitcode = SDL_Init(SDL_INIT_EVERYTHING);

	if (exitcode == 0)
	{
		GOOD("GESTOR DE VIDEO CREADO.");
	}
	else
	{
		ERROR("NO SE HA PODIDO CREAR EL GESTOR DE VIDEO.");
		exit(1);
	}
}

VideoManager::~VideoManager()
{
}

int VideoManager::getProcessTime()
{
	return SDL_GetTicks();
}

VideoManager* VideoManager::getInstance()
{
	if (pInstance == nullptr)
		pInstance = new VideoManager();

	return pInstance;
}

void VideoManager::createWindow(const char* Title, int width, int height)
{
	LOG("CREANDO VENTANA...");
	gWindow = SDL_CreateWindow(Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (gWindow != NULL)
	{
		GOOD("VENTANA CREADA.");
	}
	else
	{
		ERROR("NO SE HA PODIDO CREAR LA VENTANA.");
		exit(1);
	}

	LOG("CREANDO RENDERER...");
	GPU = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_PRESENTVSYNC);

	if (GPU != NULL)
	{
		GOOD("RENDERER CREADO.");
	}
	else
	{
		ERROR("NO SE HA PODIDO CREAR EL RENDERER.");
		exit(1);
	}
}

void VideoManager::renderGraphic(int graphicId, int posX, int posY, int width, int height)
{
	SDL_Rect r, rectAux;

	r.x = posX;
	r.y = posY;
	r.w = width;
	r.h = height;

	rectAux.x = 0;
	rectAux.y = 0;
	rectAux.w = width;
	rectAux.h = height;

	SDL_Texture* origin = ResourceManager::getInstance()->getGraphicByID(graphicId);
	SDL_RenderCopy(GPU, origin, &rectAux, &r);
}

void VideoManager::clearScreen(int R, int G, int B, int A)
{
	SDL_SetRenderDrawColor(GPU, R, G, B, A);
	SDL_RenderClear(GPU);
}

void VideoManager::updateScreen()
{
	SDL_RenderPresent(GPU);
}

void VideoManager::waitTime(int ms)
{
	SDL_Delay(ms);
}

int VideoManager::autoWaitTime()
{
	int FPS;

	currentTime = SDL_GetTicks();
	deltaTime = currentTime - lastTime;
	FPS = (1000.0f / deltaTime);

	if (deltaTime < (int)msFrame)
	{
		SDL_Delay((int)msFrame - deltaTime);
	}

	lastTime = currentTime;

	return FPS;
}

void VideoManager::close()
{
	LOG("DESTRUYENDO VENTANA...");
	SDL_DestroyWindow(gWindow);
	LOG("CERRANDO APLICACION...");
	SDL_Quit();
}