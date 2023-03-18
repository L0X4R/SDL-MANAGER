#include "Scene.h"

Scene::Scene()
{
	needReinit = true;
}

Scene::~Scene()
{
}

void Scene::init()
{
	needReinit = false;
	loadXMLevel();
}

void Scene::reinit()
{
	needReinit = true;
}

void Scene::loadXMLevel()
{
}
