#include "InputManager.h"

InputManager* InputManager::pInstance = NULL;

InputManager::InputManager()
{
	LOG("CREANDO GESTOR DE INPUTS.");
}

InputManager* InputManager::getInstance()
{
	if (pInstance == nullptr)
		pInstance = new InputManager();

	return pInstance;
}

InputManager::~InputManager()
{
}

void InputManager::update()
{
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			close_game = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				key_escape = true;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_W)
			{
				key_w = true;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_S)
			{
				key_s = true;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_A)
			{
				key_a = true;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_D)
			{
				key_d = true;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_COMMA)
			{
				key_comma = true;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{
				key_space = true;
			}
			break;
		case SDL_KEYUP:
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				key_escape = false;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_W)
			{
				key_w = false;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_S)
			{
				key_s = false;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_A)
			{
				key_a = false;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_D)
			{
				key_d = false;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_COMMA)
			{
				key_comma = false;
			}

			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{
				key_space = false;
			}
			break;
		default:
			break;
		}
	}
}
