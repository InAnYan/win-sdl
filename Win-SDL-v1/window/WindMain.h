// WIN-SDL - attempt to create windows library in C++ with SDL.
// Copyright(C) 2022 Ruslan Popov

#ifndef WIND_MAIN_H
#define WIND_MAIN_H

#include "win-sdl.h"

class SWindow;

class WindMain
{
public:
   void doRender();
   void doEvents(SDL_Event* e);
   void doLogic();

   void addWindow(shared_ptr<SWindow> window);
   static void deleteWindow(shared_ptr<SWindow> window);
   static void deleteActiveWindow();

   static SDL_Point getDimensions();

   WindMain(SDL_Window* window, SDL_Renderer* renderer, SDL_Point dim);
   ~WindMain();

private:
   SDL_Window* mainWindow;
   SDL_Renderer* mainRenderer;

   SDL_Point mousePos, clickOffset;
   static SDL_Point screen;
   bool resize, leftMouseButtonDown, superMode;

   static std::vector<shared_ptr<SWindow>> SWindows;
};

#endif
