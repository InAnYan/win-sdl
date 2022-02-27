// WIN-SDL - attempt to create windows library in C++ with SDL.
// Copyright(C) 2022 Ruslan Popov

#ifndef COMPONENT_H
#define COMPONENT_H

#include "win-sdl.h"

class SWindow;

class Component
{
	friend class SWindow;

public:
	virtual void doDraw() = 0;
	virtual void doEvents(SDL_Event* e) = 0;
	virtual void doLogic() = 0;

	Component(std::string n, SDL_Rect b);
	virtual ~Component() = 0;

	SDL_Rect bounds;
	bool active;
	std::string name;

private:
	SDL_Renderer* renderer;
	int offsetX;
	int offsetY;
	SWindow* parent;
};

#endif
