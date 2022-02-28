// WIN-SDL - attempt to create windows library in C++ with SDL.
// Copyright(C) 2022 Ruslan Popov

#ifndef SWINDOW_H
#define SWINDOW_H

#include "win-sdl.h"

class Component;

class SWindow
{
	friend class WindMain;
public:
	SWindow(std::string n, SDL_Rect b);
	~SWindow();

	void addComponent(Component* c);
	void deleteComponent(Component* c);

	std::string name;
	SDL_Color bgColor;

	SDL_Rect getBounds();
	void setBounds(SDL_Rect r);

protected:
	virtual void doDraw();
	virtual void doEvents(SDL_Event* e);
	virtual void doLogic();

	SDL_Renderer* renderer;
	SDL_Rect bounds, oldBounds;
	bool active;

private:
	//bool accessible;
	std::vector<Component*> components;
};

#endif
