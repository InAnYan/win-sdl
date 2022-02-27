// WIN-SDL - attempt to create windows library in C++ with SDL.
// Copyright(C) 2022 Ruslan Popov

#ifndef WIN_GRAPHICS
#define WIN_GRAPHICS

#include <SDL/SDL.h>

#define WHITE_CS {0xFF, 0xFF, 0xFF, 0xFF}
#define BLACK_CS {0x00, 0x00, 0x00, 0xFF}

#ifndef WIN_STYLE_OVERWRITE
#define WINDOW_BG_CS  {0xC6, 0xB2, 0xA8, 0xFF}

#define WINDOW_T_CS    {0xED, 0xA8, 0x70, 0xFF}
#define WINDOW_DT_CS  {0x7D, 0x59, 0x3B, 0xFF}
#define WINDOW_LT_CS  {0xF7, 0xD9, 0xC0, 0xFF}
#define WINDOW_RDT_CS   {0x70, 0x4F, 0x35, 0xFF} // -
#define WINDOW_RLT_CS   {0x0A, 0x31, 0x50, 0xFF} // -

#define WINDOW_TITLE_HEIGHT 20 // TODO: Magic formula with font size. Maybe
#define WINDOW_TBUTTONS_SPACE 1

#define POPUP_TIME_MS 2500
#endif

void drawLineThick(SDL_Renderer* renderer, SDL_Rect coords, unsigned int thickness, SDL_Color color);
void drawRectThick(SDL_Renderer* renderer, SDL_Rect coords, unsigned int thickness, SDL_Color lcolor, SDL_Color rcolor);
void drawRectThickBump(SDL_Renderer* renderer, SDL_Rect coords, unsigned int thickness, SDL_Color lcolor, SDL_Color dcolor, SDL_Color rcolor);
void drawRectThickBumpV(SDL_Renderer* renderer, SDL_Rect coords, unsigned int thickness, SDL_Color lcolor, SDL_Color dcolor, SDL_Color rcolor);
void drawAbsRectThickBump(SDL_Renderer* renderer, SDL_Rect coords, unsigned int thickness, SDL_Color lcolor, SDL_Color dcolor, SDL_Color rcolor);
void drawAbsRectThickBump(SDL_Renderer* renderer, SDL_Rect coords, unsigned int thickness, SDL_Color lcolor, SDL_Color dcolor);

#endif