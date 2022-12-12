#pragma region INCLUDES
#include <iostream>

#include "ResourceManager.h"
#include "VideoManager.h"
#include "AudioManager.h"

using namespace std;
#pragma endregion

int main(int argc, char* args[])
{
#pragma region SETUP
	VideoManager* WINDOW = VideoManager::getInstance();
	WINDOW->createWindow("WINDOW TITLE", 1280, 720);

	ResourceManager* RESOURCES = ResourceManager::getInstance();

	AudioManager* AUDIO = AudioManager::getInstance();

	SDL_Event event;
#pragma endregion
	bool endProcess = false;

	while (!endProcess)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				endProcess = true;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					endProcess = true;
				break;
			default:
				break;
			}
		}

		WINDOW->updateScreen();
		WINDOW->clearScreen(0, 0, 0, 255);

#pragma region WAIT TIME AND FPS
		int FPS = WINDOW->autoWaitTime();

		if (WINDOW->getProcessTime() % 250 <= 10)
		{
			printf("FPS: %d\r", FPS);
		}
#pragma endregion
	}

	WINDOW->close();

	return 0;
}