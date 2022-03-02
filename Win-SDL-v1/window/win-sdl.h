// WIN-SDL - attempt to create windows library in C++ with SDL.
// Copyright(C) 2022 Ruslan Popov

#ifndef WIN_SDL_H
#define WIN_SDL_H

#include <memory>

#ifdef __linux__
#   include <SDL2/SDL.h>
#else
#   include <SDL/SDL.h>
#endif // __linux__

#include <vector>
#include <memory>
#include <functional>

#include "../log/logger.h"

#include "WinGraphics.h"
#include "Component.h"
#include "SWindow.h"
#include "WindMain.h"
//#include "BasicWindows.h"

#endif
