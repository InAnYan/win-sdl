// WIN-SDL - attempt to create windows library in C++ with SDL.
// Copyright(C) 2022 Ruslan Popov

#include "BasicWindows.h"
#include "WinGraphics.h"
#include "WindMain.h"

#define FULL_TITLE_REGION {bounds.x+4, bounds.y+4, bounds.w-8, WINDOW_TITLE_HEIGHT}
#define TITLE_REGION {bounds.x+5, bounds.y+5, bounds.w-11-WINDOW_TITLE_HEIGHT*3-WINDOW_TBUTTONS_SPACE*3, WINDOW_TITLE_HEIGHT-2}
#define BUTTON_UND_REGION {bounds.x + bounds.w-11 - WINDOW_TITLE_HEIGHT*3 + WINDOW_TBUTTONS_SPACE*4, bounds.y+5, WINDOW_TITLE_HEIGHT, WINDOW_TITLE_HEIGHT-2}
#define BUTTON_MAX_REGION {bounds.x + bounds.w-11 - WINDOW_TITLE_HEIGHT*2 + WINDOW_TBUTTONS_SPACE*6, bounds.y+5, WINDOW_TITLE_HEIGHT, WINDOW_TITLE_HEIGHT-2}
#define BUTTON_CLOSE_REGION {bounds.x + bounds.w-11 - WINDOW_TITLE_HEIGHT + WINDOW_TBUTTONS_SPACE*8, bounds.y+5, WINDOW_TITLE_HEIGHT-1, WINDOW_TITLE_HEIGHT-2}

#define MBOUNDS {0, 0, WindMain::getDimensions().x, WindMain::getDimensions().y}

void nullFunc(BasicWindow* b)
{

}

BasicWindow::BasicWindow(std::string title, SDL_Rect bounds, int type) : SWindow(title, bounds)
{
	this->type = type;
	tBounds = TITLE_REGION;
	wBounds = BUTTON_UND_REGION;
	mBounds = BUTTON_MAX_REGION;
	cBounds = BUTTON_CLOSE_REGION;
	maxed = false;
	moving = false;
	wrapped = false;
	leftMouseButtonDown = false;
	mousePos = { 0 };
	clickOffset = { 0 };

	alwaysHandler = nullFunc;
	maximisedHandler = nullFunc;
	wrappedHandler = nullFunc;
	closedHandler = nullFunc;
	boundsHandler = nullFunc;
}

void BasicWindow::setBounds(SDL_Rect b)
{
	SWindow::setBounds(b);
	tBounds = TITLE_REGION;
	wBounds = BUTTON_UND_REGION;
	mBounds = BUTTON_MAX_REGION;
	cBounds = BUTTON_CLOSE_REGION;
	boundsHandler(this);
}

void BasicWindow::doDraw()
{
	if (wrapped)
	{
        oldBounds = bounds;
        bounds = {oldBounds.x, oldBounds.y, oldBounds.w, WINDOW_TITLE_HEIGHT};

		drawRectThick(renderer, bounds, 1, WINDOW_BG_CS, WINDOW_BG_CS);

		// Frame
		drawRectThickBump(renderer, bounds, 1, WINDOW_1LT_CS, WINDOW_1DT_CS, WINDOW_BG_CS);
		drawAbsRectThickBump(renderer, { bounds.x + 1, bounds.y + 1, bounds.x + bounds.w - 1, bounds.y + bounds.h - 1 }, 1, WINDOW_2LT_CS, WINDOW_2DT_CS);

		// Title
		drawRectThick(renderer, { bounds.x + 5, bounds.y + 5, bounds.w - 5, WINDOW_TITLE_HEIGHT }, 1, WINDOW_T_CS, WINDOW_T_CS);

		// Buttons
		//drawRectThickBumpV(renderer, BUTTON_UND_REGION, 1, WINDOW_T_CS, WINDOW_DT_CS, WINDOW_T_CS);
		//drawRectThickBumpV(renderer, BUTTON_MAX_REGION, 1, WINDOW_T_CS, WINDOW_DT_CS, WINDOW_T_CS);
		//drawRectThickBumpV(renderer, BUTTON_CLOSE_REGION, 1, WINDOW_T_CS, WINDOW_DT_CS, WINDOW_T_CS);

		SWindow::doDraw();
	}
	else if (maxed)
	{
		drawRectThick(renderer, bounds, 1, WINDOW_BG_CS, WINDOW_BG_CS);

		// Frame
		drawRectThickBump(renderer, bounds, 1, WINDOW_1LT_CS, WINDOW_1DT_CS, WINDOW_BG_CS);
		drawAbsRectThickBump(renderer, { bounds.x + 1, bounds.y + 1, bounds.x + bounds.w - 1, bounds.y + bounds.h - 1 }, 1, WINDOW_2LT_CS, WINDOW_2DT_CS);

		// Title
		drawRectThick(renderer, { bounds.x + 5, bounds.y + 5, bounds.w - 5, bounds.h - 5 }, 1, WINDOW_T_CS, WINDOW_T_CS);

		// Buttons
		//drawRectThickBumpV(renderer, BUTTON_UND_REGION, 1, WINDOW_T_CS, WINDOW_DT_CS, WINDOW_T_CS);
		//drawRectThickBumpV(renderer, BUTTON_MAX_REGION, 1, WINDOW_T_CS, WINDOW_DT_CS, WINDOW_T_CS);
		//drawRectThickBumpV(renderer, BUTTON_CLOSE_REGION, 1, WINDOW_T_CS, WINDOW_DT_CS, WINDOW_T_CS);

		SWindow::doDraw();
	}
	else {
		//drawRectThick(renderer, bounds, 1, WINDOW_BG_CS, WINDOW_BG_CS);

		// Frame
		drawRectThickBump(renderer, bounds, 1, WINDOW_1LT_CS, WINDOW_1DT_CS, WINDOW_BG_CS);
		drawAbsRectThickBump(renderer, { bounds.x + 1, bounds.y + 1, bounds.x + bounds.w - 1, bounds.y + bounds.h - 1 }, 1, WINDOW_2LT_CS, WINDOW_2DT_CS);

		// Title
		drawRectThick(renderer, { bounds.x + 4, bounds.y + 4, bounds.w - 8, WINDOW_TITLE_HEIGHT }, 1, WINDOW_T_CS, WINDOW_T_CS);

		// Buttons
		//drawRectThickBumpV(renderer, BUTTON_UND_REGION, 1, WINDOW_T_CS, WINDOW_DT_CS, WINDOW_T_CS);
		//drawRectThickBumpV(renderer, BUTTON_MAX_REGION, 1, WINDOW_T_CS, WINDOW_DT_CS, WINDOW_T_CS);
		//drawRectThickBumpV(renderer, BUTTON_CLOSE_REGION, 1, WINDOW_T_CS, WINDOW_DT_CS, WINDOW_T_CS);

		SWindow::doDraw();
	}
}

void BasicWindow::doEvents(SDL_Event* e)
{
	switch (e->type)
	{
	case SDL_MOUSEMOTION: // TODO: Hardcoded. Linked to #1
		mousePos = { e->motion.x, e->motion.y };
		if (leftMouseButtonDown && moving) {
			setBounds({ mousePos.x - clickOffset.x, mousePos.y - clickOffset.y, bounds.w, bounds.h });
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (leftMouseButtonDown && e->button.button == SDL_BUTTON_LEFT) {
			leftMouseButtonDown = false;
			moving = false;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (!leftMouseButtonDown && e->button.button == SDL_BUTTON_LEFT)
		{

			leftMouseButtonDown = true;
			if (SDL_PointInRect(&mousePos, &tBounds))
			{
				moving = true;
				clickOffset.x = mousePos.x - tBounds.x;
				clickOffset.y = mousePos.y - tBounds.y;
			}
		}
		if (SDL_PointInRect(&mousePos, &cBounds))
		{
			closedHandler(this);
			WindMain::deleteActiveWindow();
		}
		else if (SDL_PointInRect(&mousePos, &mBounds))
		{
			maxed = maxed == false ? maxed = true : maxed = false;
			maximisedHandler(this); // TODO: For what?
		}
		else if (SDL_PointInRect(&mousePos, &wBounds))
		{
			wrapped = wrapped == false ? wrapped = true : wrapped = false;
			wrappedHandler(this);
		}
		break;
	}

	SWindow::doEvents(e);
}

void BasicWindow::doLogic()
{
    alwaysHandler(this);
    boundsHandler(this);
	SWindow::doLogic();
}
