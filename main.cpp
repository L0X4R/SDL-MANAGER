#pragma region INCLUDES
#include "ResourceManager.h"
#include "VideoManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#pragma endregion

int main(int argc, char* args[])
{
#pragma region MANAGER SETUP
	// INSTANCIA VIDEO MANAGER + CREACION DE VENTANA.
	VideoManager* WINDOW = VideoManager::getInstance();

	WINDOW->createWindow("WINDOW TITLE", SCREEN_WIDTH, SCREEN_HEIGHT);

	// INSTANCIA RESOURCE MANAGER.
	ResourceManager* RESOURCES = ResourceManager::getInstance();

	// INSTANCIA SCENE MANAGER
	SceneManager* SCENE = SceneManager::getInstance();

	// INSTANCIA INPUT MANAGER
	InputManager* INPUT = InputManager::getInstance();

	SCENE->init();
	//SCENE->loadScene(SceneEnum::MAIN_MENU);
#pragma endregion

#pragma region INIT
	// MAIN GAME
	bool endProcess = false;
	bool endGame = false;
#pragma endregion

	while (!endProcess)
	{
		while (!endGame)
		{
			INPUT->update();

			if (INPUT->needCloseGame())
			{
				endGame = true;
				endProcess = true;
			}

			//SCENE->getLoadedScene()->update();
			//SCENE->getLoadedScene()->render();
			WINDOW->updateScreen();
			WINDOW->clearScreen(0, 0, 0, 255);
			WINDOW->autoWaitTime();
		}
	}

	WINDOW->close();
	return 0;
}