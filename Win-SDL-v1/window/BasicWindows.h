// WIN-SDL - attempt to create windows library in C++ with SDL.
// Copyright(C) 2022 Ruslan Popov

#ifndef BASIC_WINDOWS_H
#define BASIC_WINDOWS_H

//#include "win-sdl.h"
#include <functional>
#include "SWindow.h"

// I know
#define WINDOW_CLOSABLE		0x001
#define WINDOW_MAXIMISABLE	0x010
#define WINDOW_WRAPPABLE	0x100

class BasicWindow : public SWindow
{
public:
	BasicWindow(std::string title, SDL_Rect bounds, int type);

	std::function<void(BasicWindow*)> alwaysHandler;
	std::function<void(BasicWindow*)> movingHandler;
	std::function<void(BasicWindow*)> closedHandler;
	std::function<void(BasicWindow*)> wrappedHandler;
	std::function<void(BasicWindow*)> maximisedHandler;

	void setBounds(SDL_Rect b);

private:
	virtual void doDraw();
	virtual void doLogic();
	virtual void doEvents(SDL_Event* e);

	SDL_Rect tBounds, wBounds, cBounds, mBounds;
	SDL_Point mousePos, clickOffset;
	bool maxed, wrapped, moving, leftMouseButtonDown;
	int type;
};

#define DIALOG_OK		0x001
#define DIALOG_OK_CLOSE 0x010
#define DIALOG_YES_NO	0x100

class DialogBox : SWindow
{
public:
	DialogBox(std::string title, std::string prompt, int type);

	std::function<void(DialogBox*)> OKHandler;
	std::function<void(DialogBox*)> closeHandler;
	std::function<void(DialogBox*)> YESHandler;
	std::function<void(DialogBox*)> NOHandler;
private:
	void doDraw();
	void doLogic();
	void doEvents(SDL_Event* e);

	int type;
	std::string prompt;
};

class SmallWindow : SWindow
{
public:
	SmallWindow(std::string title, SDL_Rect bounds);

	std::function<void(SmallWindow*)> alwaysHandler;
	std::function<void(SmallWindow*)> closeHandler;

private:
	void doDraw();
	void doLogic();
	void doEvents(SDL_Event* e);
};

#endif