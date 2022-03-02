// WIN-SDL - attempt to create windows library in C++ with SDL.
// Copyright(C) 2022 Ruslan Popov

#include "SWindow.h"

void SWindow::doDraw()
{
	SDL_RenderSetViewport(renderer, &bounds);
	for (shared_ptr<Component> cmp : components)
	{
		cmp->doDraw();
	}
}

void SWindow::doEvents(SDL_Event* e)
{
	for (shared_ptr<Component> cmp : components)
	{
		cmp->doEvents(e);
	}
}

void SWindow::doLogic()
{
	for (shared_ptr<Component> cmp : components)
	{
		cmp->doLogic();
	}
}

void SWindow::addComponent(shared_ptr<Component> c)
{
	components.insert(components.begin(), c);
	c->renderer = this->renderer;
	logInfo("Added component \"" + c->name + "\" to window \"" + this->name + "\"");
}

void SWindow::deleteComponent(shared_ptr<Component> c)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (components[i] == c)
		{
			logDebug("Deleting window: \"" + components[i]->name + "\"");
			components.erase(components.begin() + i);
		}
	}
}

SDL_Rect SWindow::getBounds()
{
	return bounds;
}

void SWindow::setBounds(SDL_Rect b)
{
	bounds.x = b.x;
	bounds.y = b.y;
	bounds.w = b.w;
	bounds.h = b.h;
}

SWindow::SWindow(std::string n, SDL_Rect b)
{
	name = n;
	bounds = b;
	logInfo("Created window: \"" + n + "\"");
}

SWindow::~SWindow()
{
	components.clear();
}
