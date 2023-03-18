#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#pragma region INCLUDES
#include <iostream>
#include <vector>
#include "Scene.h"
#include "VideoManager.h"

// SCENES

#include "config.h"
using namespace std;
#pragma endregion

enum SceneEnum
{
	MAIN_MENU, OPTIONS_MENU,
	NOT_LOAD, _LASTSCENE
};

#define NUM_SCENES _LASTSCENE

class SceneManager
{
private:
	SceneManager();
	static SceneManager* pInstance;

	SceneEnum loadedScene;

	vector<Scene*> scenesVector;

public:
	static SceneManager* getInstance();
	~SceneManager();

	void init();

	Scene* getLoadedScene();
	void loadScene(SceneEnum SceneNum);
};
#endif