// WIN-SDL - attempt to create windows library in C++ with SDL.
// Copyright(C) 2022 Ruslan Popov

#include "WinGraphics.h"

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