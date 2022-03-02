// WIN-SDL - attempt to create windows library in C++ with SDL.
// Copyright(C) 2022 Ruslan Popov

#include "BasicWindows.h"
#include "WinGraphics.h"
#include "WindMain.h"

#define FULL_TITLE_REGION {bounds.x+4, bounds.y+4, bounds.w-8, WINDOW_TITLE_HEIGHT}
//#define TITLE_REGION {bounds.x+5, bounds.y+5, bounds.w-11-WINDOW_TITLE_HEIGHT*3-WINDOW_TBUTTONS_SPACE*3, WINDOW_TITLE_HEIGHT-2}
#define TITLE_REGION { bounds.x + 4, bounds.y + 4, bounds.w - 8- WINDOW_TITLE_HEIGHT  -WINDOW_BUTTON_WIDTH - WINDOW_TBUTTONS_SPACE -WINDOW_BUTTON_WIDTH, WINDOW_TITLE_HEIGHT }

#define BUTTON_UND_REGION {bounds.x + bounds.w-5 - WINDOW_TITLE_HEIGHT  -WINDOW_BUTTON_WIDTH - WINDOW_TBUTTONS_SPACE -WINDOW_BUTTON_WIDTH, bounds.y+6, WINDOW_BUTTON_WIDTH, WINDOW_TITLE_HEIGHT-4}
#define BUTTON_MAX_REGION {bounds.x + bounds.w-5 - WINDOW_TITLE_HEIGHT  -WINDOW_BUTTON_WIDTH - WINDOW_TBUTTONS_SPACE, bounds.y+6, WINDOW_BUTTON_WIDTH, WINDOW_TITLE_HEIGHT-4}
#define BUTTON_CLOSE_REGION {bounds.x + bounds.w-5 - WINDOW_TITLE_HEIGHT, bounds.y+6, WINDOW_BUTTON_WIDTH, WINDOW_TITLE_HEIGHT-4}

#define MBOUNDS {0, 0, WindMain::getDimensions().x, WindMain::getDimensions().y}

BasicWindow::BasicWindow(std::string title, SDL_Rect bounds, int type) : SWindow(title, bounds)
{
	this->type = type;
	tBounds = TITLE_REGION;
	wBounds = BUTTON_UND_REGION;
	mBounds = BUTTON_MAX_REGION;
	cBounds = BUTTON_CLOSE_REGION;
	moving = false;
	leftMouseButtonDown = false;
	mousePos = { 0 };
	clickOffset = { 0 };
	state = WindowState::WIN_NORMAL;
}

void BasicWindow::setBounds(SDL_Rect b)
{
	SWindow::setBounds(b);
	tBounds = TITLE_REGION;
	wBounds = BUTTON_UND_REGION;
	mBounds = BUTTON_MAX_REGION;
	cBounds = BUTTON_CLOSE_REGION;
	if(boundsHandler) boundsHandler(this);
}

void BasicWindow::doDraw()
{
    switch(state)
    {
        case WindowState::WIN_NORMAL:
            // Frame
            drawRectThickBump(renderer, bounds, 1, WINDOW_1LT_CS, WINDOW_1DT_CS, WINDOW_BG_CS);
            drawAbsRectThickBump(renderer, { bounds.x + 1, bounds.y + 1, bounds.x + bounds.w - 1, bounds.y + bounds.h - 1 }, 1, WINDOW_2LT_CS, WINDOW_2DT_CS);

            // Title
            drawRectThick(renderer, { bounds.x + 4, bounds.y + 4, bounds.w - 8, WINDOW_TITLE_HEIGHT }, 1, WINDOW_T_CS, WINDOW_T_CS);

            // Wrap button
            drawRectThickBumpV(renderer, wBounds, 1, WINDOW_2LT_CS, WINDOW_1DT_CS, WINDOW_BG_CS);
            drawRectThickBumpV(renderer, {wBounds.x+1, wBounds.y+1, wBounds.w-2, wBounds.h-2}, 1, WINDOW_BG_CS, WINDOW_2DT_CS, WINDOW_BG_CS);

            // Max button
            drawRectThickBumpV(renderer, mBounds, 1, WINDOW_2LT_CS, WINDOW_1DT_CS, WINDOW_BG_CS);
            drawRectThickBumpV(renderer, {mBounds.x+1, mBounds.y+1, mBounds.w-2, mBounds.h-2}, 1, WINDOW_BG_CS, WINDOW_2DT_CS, WINDOW_BG_CS);

            // Close button
            drawRectThickBumpV(renderer, cBounds, 1, WINDOW_2LT_CS, WINDOW_1DT_CS, WINDOW_BG_CS);
            drawRectThickBumpV(renderer, {cBounds.x+1, cBounds.y+1, cBounds.w-2, cBounds.h-2}, 1, WINDOW_BG_CS, WINDOW_2DT_CS, WINDOW_BG_CS);
            break;
        case WindowState::WIN_MAXED:
            // Frame
            drawRectThickBump(renderer, bounds, 1, WINDOW_1LT_CS, WINDOW_1DT_CS, WINDOW_BG_CS);
            drawAbsRectThickBump(renderer, { bounds.x + 1, bounds.y + 1, bounds.x + bounds.w - 1, bounds.y + bounds.h - 1 }, 1, WINDOW_2LT_CS, WINDOW_2DT_CS);

            // Title
            drawRectThick(renderer, { bounds.x + 4, bounds.y + 4, bounds.w - 8, WINDOW_TITLE_HEIGHT }, 1, WINDOW_T_CS, WINDOW_T_CS);

            // Wrap button
            drawRectThickBumpV(renderer, wBounds, 1, WINDOW_2LT_CS, WINDOW_1DT_CS, WINDOW_BG_CS);
            drawRectThickBumpV(renderer, {wBounds.x+1, wBounds.y+1, wBounds.w-2, wBounds.h-2}, 1, WINDOW_BG_CS, WINDOW_2DT_CS, WINDOW_BG_CS);

            // Max button
            drawRectThickBumpV(renderer, mBounds, 1, WINDOW_2LT_CS, WINDOW_1DT_CS, WINDOW_BG_CS);
            drawRectThickBumpV(renderer, {mBounds.x+1, mBounds.y+1, mBounds.w-2, mBounds.h-2}, 1, WINDOW_BG_CS, WINDOW_2DT_CS, WINDOW_BG_CS);

            // Close button
            drawRectThickBumpV(renderer, cBounds, 1, WINDOW_2LT_CS, WINDOW_1DT_CS, WINDOW_BG_CS);
            drawRectThickBumpV(renderer, {cBounds.x+1, cBounds.y+1, cBounds.w-2, cBounds.h-2}, 1, WINDOW_BG_CS, WINDOW_2DT_CS, WINDOW_BG_CS);
            break;
        case WindowState::WIN_WRAPPED:
            // Frame
            drawRectThickBump(renderer, bounds, 1, WINDOW_1LT_CS, WINDOW_1DT_CS, WINDOW_BG_CS);
            drawAbsRectThickBump(renderer, { bounds.x + 1, bounds.y + 1, bounds.x + bounds.w - 1, bounds.y + bounds.h - 1 }, 1, WINDOW_2LT_CS, WINDOW_2DT_CS);

            // Title
            drawRectThick(renderer, { bounds.x + 4, bounds.y + 4, bounds.w - 8, WINDOW_TITLE_HEIGHT }, 1, WINDOW_T_CS, WINDOW_T_CS);

            // Wrap button
            drawRectThickBumpV(renderer, wBounds, 1, WINDOW_2LT_CS, WINDOW_1DT_CS, WINDOW_BG_CS);
            drawRectThickBumpV(renderer, {wBounds.x+1, wBounds.y+1, wBounds.w-2, wBounds.h-2}, 1, WINDOW_BG_CS, WINDOW_2DT_CS, WINDOW_BG_CS);

            // Max button
            drawRectThickBumpV(renderer, mBounds, 1, WINDOW_2LT_CS, WINDOW_1DT_CS, WINDOW_BG_CS);
            drawRectThickBumpV(renderer, {mBounds.x+1, mBounds.y+1, mBounds.w-2, mBounds.h-2}, 1, WINDOW_BG_CS, WINDOW_2DT_CS, WINDOW_BG_CS);

            // Close button
            drawRectThickBumpV(renderer, cBounds, 1, WINDOW_2LT_CS, WINDOW_1DT_CS, WINDOW_BG_CS);
            drawRectThickBumpV(renderer, {cBounds.x+1, cBounds.y+1, cBounds.w-2, cBounds.h-2}, 1, WINDOW_BG_CS, WINDOW_2DT_CS, WINDOW_BG_CS);
            break;
    }
    SWindow::doDraw();
}

void BasicWindow::doEvents(SDL_Event* e)
{
	switch (e->type)
	{
	case SDL_MOUSEMOTION: // TODO: Hardcoded. Linked to #1
		mousePos = { e->motion.x, e->motion.y };
		if (leftMouseButtonDown && moving && state != WindowState::WIN_MAXED) {
			setBounds({ mousePos.x - clickOffset.x, mousePos.y - clickOffset.y, bounds.w, bounds.h }); // TODO: Optimize
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (leftMouseButtonDown && e->button.button == SDL_BUTTON_LEFT) {
			leftMouseButtonDown = false;
			moving = false;
			if (SDL_PointInRect(&mousePos, &cBounds))
            {
                if(closedHandler) closedHandler(this);
                WindMain::deleteActiveWindow();
            }
            else if (SDL_PointInRect(&mousePos, &mBounds))
            {
                if (state == WindowState::WIN_MAXED)
                {
                    setBounds(oldBounds);
                    state = WindowState::WIN_NORMAL;
                }
                else if (state == WindowState::WIN_WRAPPED)
                {
                    oldBounds = {bounds.x, bounds.y, oldBounds.w, oldBounds.h};
                    setBounds({0, 0, WindMain::getDimensions().x, WindMain::getDimensions().x});
                    state = WindowState::WIN_MAXED;
                }
                else
                {
                    oldBounds = bounds;
                    setBounds({0, 0, WindMain::getDimensions().x, WindMain::getDimensions().x});
                    state = WindowState::WIN_MAXED;
                }
                if(maximisedHandler) maximisedHandler(this); // TODO: For what?
            }
            else if (SDL_PointInRect(&mousePos, &wBounds))
            {
                if (state == WindowState::WIN_WRAPPED)
                {
                    setBounds({bounds.x, bounds.y, oldBounds.w, oldBounds.h});
                    state = WindowState::WIN_NORMAL;
                }
                else
                {
                    oldBounds = bounds;
                    setBounds({oldBounds.x, oldBounds.y, oldBounds.w, WINDOW_TITLE_HEIGHT+8});
                    state = WindowState::WIN_WRAPPED;
                }
                if(wrappedHandler) wrappedHandler(this);
            }
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
		break;
	}

	SWindow::doEvents(e);
}

void BasicWindow::doLogic()
{
    if(alwaysHandler) alwaysHandler(this);
    if(alwaysHandler) boundsHandler(this);
	SWindow::doLogic();
}
