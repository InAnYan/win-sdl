// WIN-SDL - attempt to create windows library in C++ with SDL.
// Copyright(C) 2022 Ruslan Popov

#include "WindMain.h"

// TODO: SWindows[0] :<
#define S_END SWindows.back()

void WindMain::doRender()
{
	for (shared_ptr<SWindow> win : SWindows)
	{
		SDL_RenderSetViewport(mainRenderer, NULL);
		win->doDraw();
	}
}

void WindMain::doEvents(SDL_Event* e)
{
	if (!SWindows.empty())
	{
		switch (e->type)
		{
		case SDL_MOUSEMOTION:
			mousePos = { e->motion.x, e->motion.y };
			for (shared_ptr<SWindow> win : SWindows) // TODO: Hardcoded. Linked to #1
			{
				win->doEvents(e);
			}
			return;
			break;
		case SDL_MOUSEBUTTONUP:
			if (leftMouseButtonDown && e->button.button == SDL_BUTTON_LEFT) {
				leftMouseButtonDown = false;
				resize = false;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (!leftMouseButtonDown && e->button.button == SDL_BUTTON_LEFT)
			{
				leftMouseButtonDown = true;
				bool overlap = false;
				for (int i = SWindows.size()-2; i >= 0 ; i--)
				{
					if (SDL_PointInRect(&mousePos, &SWindows[i]->bounds)) // && !)
					{
						for (int j = 1; j <= SWindows.size() - 1 - i; j++)
						{
							if (SDL_PointInRect(&mousePos, &SWindows[i + j]->bounds))
							{
								overlap = true;
								break;
							}
						}
						if (!overlap)
						{
							shared_ptr<SWindow> temp = SWindows[i];
							S_END->active = false;
							SWindows.erase(SWindows.begin() + i);
							SWindows.push_back(temp);
							S_END->active = true;
							break;
						}
					}
				}
			}
			break;
		}
		S_END->doEvents(e);
	}
}

void WindMain::doLogic()
{
	for (shared_ptr<SWindow> win : SWindows)
	{
		win->doLogic();
	}
}

void WindMain::addWindow(shared_ptr<SWindow> window)
{
	SWindows.push_back(window);
	window->renderer = mainRenderer;
	logInfo("Added window: \"" + window->name + "\"");
	window->active = true;
}

WindMain::WindMain(SDL_Window* window, SDL_Renderer* renderer, SDL_Point dim)
{
	mainWindow = window;
	mainRenderer = renderer;
	logInfo("Created window manager");
	clickOffset = { 0 };
	mousePos = { 0 };
	leftMouseButtonDown = false;
	resize = false;
	screen = dim;
	superMode = false;
}

SDL_Point WindMain::getDimensions()
{
	return screen;
}

void WindMain::deleteWindow(shared_ptr<SWindow> w)
{
	for (int i = 0; i < SWindows.size(); i++)
	{
		if (SWindows[i] == w)
		{
			logDebug("Deleting window: \"" + SWindows[i]->name + "\"");
			SWindows.erase(SWindows.begin()+i);
		}
	}
}

void WindMain::deleteActiveWindow()
{
	SWindows.pop_back();
}

WindMain::~WindMain()
{
	SWindows.clear();
}