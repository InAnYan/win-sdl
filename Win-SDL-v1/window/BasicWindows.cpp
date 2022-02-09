// WIN-SDL - attempt to create windows library in C++ with SDL.
// Copyright(C) 2022 Ruslan Popov

#include "BasicWindows.h"

#define FULL_TITLE_REGION {bounds.x+4, bounds.y+4, bounds.w-8, WINDOW_T_HEIGHT}
#define TITLE_REGION {bounds.x+5, bounds.y+5, bounds.w-11-WINDOW_T_HEIGHT*3-WINDOW_TBUTTONS_SPACE*3, WINDOW_T_HEIGHT-2}
#define BUTTON_UND_REGION {bounds.x + bounds.w-11 - WINDOW_T_HEIGHT*3 + WINDOW_TBUTTONS_SPACE*4, bounds.y+5, WINDOW_T_HEIGHT, WINDOW_T_HEIGHT-2}
#define BUTTON_MAX_REGION {bounds.x + bounds.w-11 - WINDOW_T_HEIGHT*2 + WINDOW_TBUTTONS_SPACE*6, bounds.y+5, WINDOW_T_HEIGHT, WINDOW_T_HEIGHT-2}
#define BUTTON_CLOSE_REGION {bounds.x + bounds.w-11 - WINDOW_T_HEIGHT + WINDOW_TBUTTONS_SPACE*8, bounds.y+5, WINDOW_T_HEIGHT-1, WINDOW_T_HEIGHT-2}

void drawLineThick(SDL_Renderer* renderer, SDL_Rect coords, unsigned int thickness, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	/*
	if(thickness % 2 == 0) {
	   for(unsigned int left = 1; left < thickness/2; left++) {
		  SDL_RenderDrawLine(renderer, coords.x+left, coords.y+left, coords.w+left, coords.h+left);
	   }

	   for(unsigned int right = 0; right < thickness/2; right++) {
		  SDL_RenderDrawLine(renderer, coords.x-right, coords.y-right, coords.w-right, coords.h-right);
	   }
	} else {
	   for(unsigned int left = 1; left < thickness/2; left++) {
		  SDL_RenderDrawLine(renderer, coords.x+left, coords.y+left, coords.w+left, coords.h+left);
	   }
	   SDL_RenderDrawLine(renderer, coords.x, coords.y, coords.w, coords.h);
	   for(unsigned int right = 1; right < thickness/2; right++) {
		  SDL_RenderDrawLine(renderer, coords.x-right, coords.y-right, coords.w-right, coords.h-right);
	   }
	}
	*/
	SDL_RenderDrawLine(renderer, coords.x, coords.y, coords.w, coords.h);
}

void drawRectThick(SDL_Renderer* renderer, SDL_Rect coords, unsigned int thickness, SDL_Color lcolor, SDL_Color rcolor)
{
	SDL_SetRenderDrawColor(renderer, rcolor.r, rcolor.g, rcolor.b, rcolor.a);
	SDL_RenderFillRect(renderer, &coords);

	SDL_SetRenderDrawColor(renderer, lcolor.r, lcolor.g, lcolor.b, lcolor.a);
	drawLineThick(renderer, { coords.x, coords.y, coords.x + coords.w, coords.y }, thickness, lcolor);                            // -----
	drawLineThick(renderer, { coords.x, coords.y, coords.x, coords.y + coords.h }, thickness, lcolor);                            // |
	drawLineThick(renderer, { coords.x + coords.w, coords.y, coords.x + coords.w, coords.y + coords.h }, thickness, lcolor);                 //     |
	drawLineThick(renderer, { coords.x, coords.y + coords.h, coords.x + coords.w, coords.y + coords.h }, thickness, lcolor);      // -----
}

void drawRectThickBump(SDL_Renderer* renderer, SDL_Rect coords, unsigned int thickness, SDL_Color lcolor, SDL_Color dcolor, SDL_Color rcolor)
{
	SDL_SetRenderDrawColor(renderer, rcolor.r, rcolor.g, rcolor.b, rcolor.a);
	SDL_RenderFillRect(renderer, &coords);

	SDL_SetRenderDrawColor(renderer, dcolor.r, dcolor.g, dcolor.b, rcolor.a);
	drawLineThick(renderer, { coords.x + coords.w, coords.y, coords.x + coords.w, coords.y + coords.h }, thickness, dcolor);      //     |
	drawLineThick(renderer, { coords.x, coords.y + coords.h, coords.x + coords.w, coords.y + coords.h }, thickness, dcolor);      // -----

	SDL_SetRenderDrawColor(renderer, lcolor.r, lcolor.g, lcolor.b, rcolor.a);
	drawLineThick(renderer, { coords.x, coords.y, coords.x + coords.w, coords.y }, thickness, lcolor);                            // -----
	drawLineThick(renderer, { coords.x, coords.y, coords.x, coords.y + coords.h }, thickness, lcolor);                            // |
}

void drawRectThickBumpV(SDL_Renderer* renderer, SDL_Rect coords, unsigned int thickness, SDL_Color lcolor, SDL_Color dcolor, SDL_Color rcolor)
{
	SDL_SetRenderDrawColor(renderer, rcolor.r, rcolor.g, rcolor.b, rcolor.a);
	SDL_RenderFillRect(renderer, &coords);

	SDL_SetRenderDrawColor(renderer, lcolor.r, lcolor.g, lcolor.b, rcolor.a);
	drawLineThick(renderer, { coords.x, coords.y, coords.x + coords.w, coords.y }, thickness, lcolor);                            // -----
	drawLineThick(renderer, { coords.x, coords.y, coords.x, coords.y + coords.h }, thickness, lcolor);                            // |

	SDL_SetRenderDrawColor(renderer, dcolor.r, dcolor.g, dcolor.b, rcolor.a);
	drawLineThick(renderer, { coords.x + coords.w, coords.y, coords.x + coords.w, coords.y + coords.h }, thickness, dcolor);      //     |
	drawLineThick(renderer, { coords.x, coords.y + coords.h, coords.x + coords.w, coords.y + coords.h }, thickness, dcolor);      // -----
}

void drawAbsRectThickBump(SDL_Renderer* renderer, SDL_Rect coords, unsigned int thickness, SDL_Color lcolor, SDL_Color dcolor, SDL_Color rcolor)
{
	SDL_SetRenderDrawColor(renderer, rcolor.r, rcolor.g, rcolor.b, rcolor.a);
	SDL_RenderFillRect(renderer, &coords);

	SDL_SetRenderDrawColor(renderer, dcolor.r, dcolor.g, dcolor.b, dcolor.a);
	drawLineThick(renderer, { coords.w, coords.y, coords.w, coords.h }, thickness, dcolor);      //     |
	drawLineThick(renderer, { coords.x, coords.h, coords.w, coords.h }, thickness, dcolor);      // -----

	SDL_SetRenderDrawColor(renderer, lcolor.r, lcolor.g, lcolor.b, lcolor.a);
	drawLineThick(renderer, { coords.x, coords.y, coords.w, coords.y }, thickness, lcolor);                            // -----
	drawLineThick(renderer, { coords.x, coords.y, coords.x, coords.h }, thickness, lcolor);                            // |
}

void drawAbsRectThickBump(SDL_Renderer* renderer, SDL_Rect coords, unsigned int thickness, SDL_Color lcolor, SDL_Color dcolor)
{
	SDL_SetRenderDrawColor(renderer, dcolor.r, dcolor.g, dcolor.b, dcolor.a);
	drawLineThick(renderer, { coords.w, coords.y, coords.w, coords.h }, thickness, dcolor);      //     |
	drawLineThick(renderer, { coords.x, coords.h, coords.w, coords.h }, thickness, dcolor);      // -----

	SDL_SetRenderDrawColor(renderer, lcolor.r, lcolor.g, lcolor.b, lcolor.a);
	drawLineThick(renderer, { coords.x, coords.y, coords.w, coords.y }, thickness, lcolor);                            // -----
	drawLineThick(renderer, { coords.x, coords.y, coords.x, coords.h }, thickness, lcolor);                            // |
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
}

void BasicWindow::setBounds(SDL_Rect b)
{
	SWindow::setBounds(b);
	tBounds = TITLE_REGION;
	wBounds = BUTTON_UND_REGION;
	mBounds = BUTTON_MAX_REGION;
	cBounds = BUTTON_CLOSE_REGION;
}

void BasicWindow::doDraw()
{
	drawRectThick(renderer, bounds, 1, WINDOW_BG_CS, WINDOW_BG_CS);

	// Frame
	drawRectThickBump(renderer, bounds, 1, WINDOW_LT_CS, WINDOW_DT_CS, WINDOW_BG_CS);
	drawAbsRectThickBump(renderer, { bounds.x + 1, bounds.y + 1, bounds.x + bounds.w - 1, bounds.y + bounds.h - 1 }, 1, WINDOW_T_CS, WINDOW_T_CS);
	drawAbsRectThickBump(renderer, { bounds.x + 2, bounds.y + 2, bounds.x + bounds.w - 2, bounds.y + bounds.h - 2 }, 1, WINDOW_T_CS, WINDOW_T_CS);
	drawAbsRectThickBump(renderer, { bounds.x + 3, bounds.y + 3, bounds.x + bounds.w - 3, bounds.y + bounds.h - 3 }, 1, WINDOW_DT_CS, WINDOW_LT_CS);

	// Title
	drawRectThick(renderer, FULL_TITLE_REGION, 1, WINDOW_LT_CS, WINDOW_LT_CS);
	drawRectThickBumpV(renderer, TITLE_REGION, 1, WINDOW_T_CS, WINDOW_DT_CS, WINDOW_T_CS);

	// Buttons
	drawRectThickBumpV(renderer, BUTTON_UND_REGION, 1, WINDOW_T_CS, WINDOW_DT_CS, WINDOW_T_CS);
	drawRectThickBumpV(renderer, BUTTON_MAX_REGION, 1, WINDOW_T_CS, WINDOW_DT_CS, WINDOW_T_CS);
	drawRectThickBumpV(renderer, BUTTON_CLOSE_REGION, 1, WINDOW_T_CS, WINDOW_DT_CS, WINDOW_T_CS);

	SWindow::doDraw();
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
			if (closedHandler) closedHandler(this);
			WindMain::deleteActiveWindow();
		}
		else if (SDL_PointInRect(&mousePos, &mBounds))
		{
			maxed = maxed == false ? maxed = true : maxed = false;
			if (maximisedHandler) maximisedHandler(this); // TODO: For what?
		}
		else if (SDL_PointInRect(&mousePos, &wBounds))
		{
			wrapped = wrapped == false ? wrapped = true : wrapped = false;
			if (wrappedHandler) wrappedHandler(this);
		}
		break;
	}

	SWindow::doEvents(e);
}

void BasicWindow::doLogic()
{
	if (alwaysHandler) alwaysHandler(this);
	if (movingHandler && moving) movingHandler(this);
	SWindow::doLogic();
}