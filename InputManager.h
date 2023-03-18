#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#pragma region INCLUDES
#include <iostream>
#include "SDL.h"
#include "config.h"
using namespace std;
#pragma endregion

class InputManager
{
private:
	InputManager();
	static InputManager* pInstance;
	SDL_Event event;

	bool key_w = false;
	bool key_a = false;
	bool key_s = false;
	bool key_d = false;
	bool key_space = false;
	bool key_escape = false;
	bool key_comma = false;
	bool close_game = false;

public:
	static InputManager* getInstance();
	~InputManager();
	void update();

	bool isKey_W()
	{
		return key_w;
	}

	bool isKey_A()
	{
		return key_a;
	}

	bool isKey_S()
	{
		return key_s;
	}

	bool isKey_D()
	{
		return key_d;
	}

	bool isKey_Space()
	{
		return key_space;
	}

	bool isKey_Esc()
	{
		return key_escape;
	}

	bool isKey_Comma()
	{
		return key_comma;
	}

	bool needCloseGame()
	{
		return close_game;
	}
};
#endif