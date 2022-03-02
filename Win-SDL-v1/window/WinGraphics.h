// WIN-SDL - attempt to create windows library in C++ with SDL.
// Copyright(C) 2022 Ruslan Popov

#ifndef WIN_GRAPHICS
#define WIN_GRAPHICS

#ifdef __linux__
#   include <SDL2/SDL.h>
#else
#   include <SDL/SDL.h>
#endif // __linux__

#define WHITE_CS {0xFF, 0xFF, 0xFF, 0xFF}
#define BLACK_CS {0x00, 0x00, 0x00, 0xFF}

#ifndef WIN_STYLE_OVERWRITE
    #define WINDOW_BG_CS     {0xD5, 0xD0, 0xCD, 0xFF}

    #define WINDOW_T_CS      {0x33, 0x4F, 0x8F, 0xFF} // TODO: Add gradient

    #define WINDOW_1DT_CS    {0x42, 0x42, 0x42, 0xFF}
    #define WINDOW_1LT_CS    {0xD3, 0xD0, 0xC6, 0xFF}
    #define WINDOW_2DT_CS    {0x7F, 0x7F, 0x7F, 0xFF}
    #define WINDOW_2LT_CS    {0xFF, 0xFF, 0xFF, 0xFF}

    #define WINDOW_TITLE_HEIGHT 20 // TODO: Magic formula with font size. Maybe
    #define WINDOW_BUTTON_WIDTH WINDOW_TITLE_HEIGHT-1
    #define WINDOW_TBUTTONS_SPACE 2

    #define POPUP_TIME_MS 2500
#endif

void drawLineThick(SDL_Renderer* renderer, SDL_Rect coords, unsigned int thickness, SDL_Color color);
void drawRectThick(SDL_Renderer* renderer, SDL_Rect coords, unsigned int thickness, SDL_Color lcolor, SDL_Color rcolor);
void drawRectThickBump(SDL_Renderer* renderer, SDL_Rect coords, unsigned int thickness, SDL_Color lcolor, SDL_Color dcolor, SDL_Color rcolor);
void drawRectThickBumpV(SDL_Renderer* renderer, SDL_Rect coords, unsigned int thickness, SDL_Color lcolor, SDL_Color dcolor, SDL_Color rcolor);
void drawAbsRectThickBump(SDL_Renderer* renderer, SDL_Rect coords, unsigned int thickness, SDL_Color lcolor, SDL_Color dcolor, SDL_Color rcolor);
void drawAbsRectThickBump(SDL_Renderer* renderer, SDL_Rect coords, unsigned int thickness, SDL_Color lcolor, SDL_Color dcolor);

#endif
