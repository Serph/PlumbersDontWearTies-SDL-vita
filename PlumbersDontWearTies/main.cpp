#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>
#include <psp2/touch.h>
#include <psp2/audioout.h>

#include "main.h"

#include <iostream>

int main(int argc, char** args)
{
	// Initialize SDL

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0)
	{
		SDL_LogCritical(0, "Error initializing SDL: %s", SDL_GetError());
		return 1;
	}

	// Create window

	SDL_Window* window = SDL_CreateWindow("Plumbers Don't Wear Ties", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 960, 544, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (window == nullptr)
	{
		SDL_LogCritical(0, "Could not create a window: %s", SDL_GetError());
		return 1;
	}

	// Initialize renderer

	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengles2");
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		SDL_LogCritical(0, "Could not create a renderer: %s", SDL_GetError());
		return -1;
	}

	// Initialize game controller

	controller = nullptr;
	controllerInstanceID = -1;
	OpenFirstAvailableController();

	// Initialize the game

	Game* game = new Game(renderer);
	game->Start();

	Uint64 previousTime = SDL_GetPerformanceCounter();

	while (game->IsRunning())
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				{
					game->Stop();
					break;
				}
				case SDL_KEYDOWN:
				{
					switch (event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							game->Stop();
							break;
						case SDLK_1:
						case SDLK_KP_1:
							game->SelectDecision(0);
							break;
						case SDLK_2:
						case SDLK_KP_2:
							game->SelectDecision(1);
							break;
						case SDLK_3:
						case SDLK_KP_3:
							game->SelectDecision(2);
							break;
						case SDLK_RIGHT:
							game->AdvancePicture();
							break;
						case SDLK_RETURN:
							if (event.key.keysym.mod & KMOD_ALT)
							{
								ToggleFullscreen(window);
							}
							break;
					}

					break;
				}
				case SDL_CONTROLLERBUTTONDOWN:
				{
					switch (event.cbutton.button)
					{
						case SDL_CONTROLLER_BUTTON_BACK:
							game->Stop();
							break;
						case SDL_CONTROLLER_BUTTON_Y:
							game->SelectDecision(0);
							break;
						case SDL_CONTROLLER_BUTTON_X:
							game->SelectDecision(1);
							break;
						case SDL_CONTROLLER_BUTTON_A:
							game->SelectDecision(2);
							break;
						case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
							game->AdvancePicture();
							break;
						case SDL_CONTROLLER_BUTTON_START:
							ToggleFullscreen(window);
							break;
					}

					break;
				}
				case SDL_CONTROLLERDEVICEADDED:
				{
					OpenFirstAvailableController();
					break;
				}
				case SDL_CONTROLLERDEVICEREMOVED:
				{
					if (event.cdevice.which == controllerInstanceID && controller != nullptr)
					{
						SDL_GameControllerClose(controller);
						controller = nullptr;
						controllerInstanceID = -1;

						SDL_Log("Controller has been disconnected: instance ID %i", event.cdevice.which);

						OpenFirstAvailableController();
					}

					break;
				}
				case SDL_WINDOWEVENT:
				{
					switch (event.window.event)
					{
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							game->WindowSizeChanged(event.window.data1, event.window.data2);
							break;
					}

					break;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		Uint64 currentTime = SDL_GetPerformanceCounter();
		double deltaSeconds = (currentTime - previousTime) / (double)SDL_GetPerformanceFrequency();
		previousTime = currentTime;

		game->Update(deltaSeconds);

		SDL_RenderPresent(renderer);
	}

	delete game;
	game = nullptr;

	if (controller != nullptr)
	{
		SDL_GameControllerClose(controller);
		controller = nullptr;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	sceKernelExitProcess(0);
	return 0;
}

void ToggleFullscreen(SDL_Window* window)
{
	bool isFullscreen = SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP;

	if (isFullscreen)
	{
		if (SDL_SetWindowFullscreen(window, 0) < 0)
			SDL_LogError(0, "Can't set the game to window mode: %s", SDL_GetError());
	}
	else
	{
		if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
			SDL_LogError(0, "Can't set the game to full screen mode: %s", SDL_GetError());
	}
}

void OpenFirstAvailableController()
{
	if (controller != nullptr) return;

	for (int j = 0; j < SDL_NumJoysticks(); j++)
	{
		if (!SDL_IsGameController(j)) continue;

		controller = SDL_GameControllerOpen(j);
		if (controller != nullptr)
		{
			SDL_Joystick* joystick = SDL_GameControllerGetJoystick(controller);
			controllerInstanceID = SDL_JoystickInstanceID(joystick);

			SDL_Log("Found new controller: index %i, instance ID %i, name %s", j, controllerInstanceID, SDL_GameControllerName(controller));

			return;
		}
	}
}
