// WIN-SDL - attempt to create windows library in C++ with SDL.
// Copyright(C) 2022 Ruslan Popov

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include <boost/date_time.hpp>
#include <fstream>

using namespace std;

/*
    Usage:
        1) Init logger by function "logInit(yourAppName, isDuplicatedToConsole)"
            e. g. "chip8emu" or (with path) "logs/chip8emu"
        2) Use log- -Info -Warning -Error -Debug for logging
        3) On exit call "logDeInit"
*/

void logInit(string p, bool d);
void logDeInit();

void logInfo(string text);
void logWarning(string text);
void logError(string text);
void logDebug(string text);

#endif
