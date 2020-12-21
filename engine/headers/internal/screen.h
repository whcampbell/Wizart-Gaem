#pragma once

#include <SDL.h>

bool initWindow();

void closeWindow();

void parseWindowEvent(SDL_WindowEvent e);

SDL_Renderer* getRenderer();
