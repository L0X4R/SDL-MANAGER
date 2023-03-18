#include "SceneManager.h"

SceneManager* SceneManager::pInstance = NULL;

SceneManager::SceneManager()
{
	LOG("CREANDO EL GESTOR DE ESCENAS.");
	loadedScene = NOT_LOAD;
}

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::getInstance()
{
	if (pInstance == nullptr)
	{
		pInstance = new SceneManager();
	}

	return pInstance;
}

void SceneManager::init()
{
	scenesVector.resize(NUM_SCENES);

	VideoManager* WINDOW = VideoManager::getInstance();

	// NEW SCENES

	// ADD SCENE BY ENUM TO VECTOR

	// INIT SCENE
}

Scene* SceneManager::getLoadedScene()
{
	return scenesVector[loadedScene];
}

void SceneManager::loadScene(SceneEnum SceneNum)
{
	loadedScene = SceneNum;
}
