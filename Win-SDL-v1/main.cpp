// WIN-SDL - attempt to create windows library in C++ with SDL.
// Copyright(C) 2022 Ruslan Popov

#pragma warning( disable: 26812 )
#pragma warning( disable: 26498 )
#pragma warning( disable: 26495 )
#pragma warning( disable: 26451 )

#include <iostream>
#include <chrono>

#define SDL_MAIN_HANDLED
#ifdef __linux__
#   include <SDL2/SDL.h>
#else
#   include <SDL/SDL.h>
#endif // __linux__

#include "log/logger.h"
#include "window/win-sdl.h"
#include "window/BasicWindows.h"

#define MS_PER_FRAME 10
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

SDL_Window* window;
SDL_Renderer* renderer;

SDL_Point WindMain::screen;
std::vector<SWindow*> WindMain::SWindows;

void deInit()
{
	logInfo("Quitting...");
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	logDebug("end");
	logDeInit();
}

int main(int argc, char** argv)
{
	logInit("logs/win-sdl-test1", true);
	logInfo("Win-sdl-v1 library test");
	logWarning("This is not completed version. Use it on your own risk");
	logInfo("Author - Ruslan Popov");
	logInfo("Email - ruslanpopov1512@gmail.com");

	logDebug("Initializing SDL...");
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		logError("Unable to init SDL: " + string(SDL_GetError()));
		deInit();
		return 3;
	}

	logDebug("Creating window...");
	window = SDL_CreateWindow("Win-sdl-v1 Test #1", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		logError("Can`t create window");
		deInit();
		return 4;
	}

    logDebug("Creating renderer...");
    #ifndef __linux__
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	#else
        SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
        renderer = SDL_CreateSoftwareRenderer(windowSurface);
	#endif // __linux__
    if (renderer == NULL)
    {
        logError("Can`t create renderer");
        deInit();
        return 5;
    }

	BasicWindow* form1 = new BasicWindow("Window 1", { 100,100,400,400 }, 0);
	BasicWindow* form2 = new BasicWindow("Window 2", { 200,100,100,400 }, 0);
	BasicWindow* form3 = new BasicWindow("Window 3", { 500,500,300,400 }, 0);

	WindMain windowManager(window, renderer, {1024, 768});
	windowManager.addWindow(form1);
	windowManager.addWindow(form2);
	windowManager.addWindow(form3);

	int temp1;
	bool running = true;
	SDL_Event e;
	while (running) {
		auto begin = std::chrono::high_resolution_clock::now();
		SDL_SetRenderDrawColor(renderer, 0x3E, 0x7C, 0x8D, 0xFF);
		SDL_RenderClear(renderer);
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) {
				running = false;
			}
			//logDebug("dpevents");
			windowManager.doEvents(&e);
			//logDebug("end");
		}
		// Logic
		//logDebug("logic");
		windowManager.doLogic();
		//form1.setBounds({100+2*i, 100+i, 400, 400});
		//i++;
		// Drawing
		//logDebug("drawing");
		windowManager.doRender();
		SDL_RenderPresent(renderer);
		#ifdef __linux__
        SDL_UpdateWindowSurface(window);
        #endif
		// FPS
		auto end = std::chrono::high_resolution_clock::now();
		temp1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
		if (MS_PER_FRAME - temp1 > 0) // TODO: What if too much?
		{
			SDL_Delay(MS_PER_FRAME - temp1);
		}
	}

	deInit();
	return 0;
}
