// WIN-SDL - attempt to create windows library in C++ with SDL.
// Copyright(C) 2022 Ruslan Popov

#ifndef BASIC_WINDOWS_H
#define BASIC_WINDOWS_H

//#include "win-sdl.h"
#include <functional>
#include "SWindow.h"

#define WINDOW_CLOSABLE		0b000001
#define WINDOW_MAXIMISABLE	0b000010
#define WINDOW_WRAPPABLE	0b000100
#define WINDOW_RESIZABLE	0b001000

enum class WindowState
{
    WIN_MAXED,
    WIN_WRAPPED,
    WIN_NORMAL
};

class BasicWindow : public SWindow
{
public:
	BasicWindow(std::string title, SDL_Rect bounds, int type);

	std::function<void(BasicWindow*)> alwaysHandler;
	std::function<void(BasicWindow*)> boundsHandler;
	std::function<void(BasicWindow*)> closedHandler;
	std::function<void(BasicWindow*)> wrappedHandler;
	std::function<void(BasicWindow*)> maximisedHandler;

	void setBounds(SDL_Rect b);

private:
	virtual void doDraw();
	virtual void doLogic();
	virtual void doEvents(SDL_Event* e);

	SDL_Rect tBounds, wBounds, cBounds, mBounds, oldBounds;
	SDL_Point mousePos, clickOffset;
	bool moving, leftMouseButtonDown;
	WindowState state;
	int type;
};

#define DIALOG_OK		0x1
#define DIALOG_OK_CLOSE 0x2
#define DIALOG_YES_NO	0x3

class DialogBox : SWindow
{
public:
	DialogBox(std::string title, std::string prompt, int type, int style);

	std::function<void(DialogBox*)> OKHandler;
	std::function<void(DialogBox*)> closeHandler;
	std::function<void(DialogBox*)> YESHandler;
	std::function<void(DialogBox*)> NOHandler;
private:
	void doDraw();
	void doLogic();
	void doEvents(SDL_Event* e);

	int type, style;
	std::string prompt;
};

class Popup : SWindow
{
public:
	// In "style" use DIALOG_*
	Popup(std::string title, std::string prompt, int style);

private:
	void doDraw();
	void doLogic();
	void doEvents(SDL_Event* e);

	int style;
	std::string prompt;
};

/*
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
*/

#endif
