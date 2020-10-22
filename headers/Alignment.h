#pragma once
#include <SDL.h>
#include "Vector.h"

struct Alignment
{
private:
	SDL_Point point;
public:
	Vector pos;
	int* x_internal = &point.x;
	int* y_internal = &point.y;
	double theta;
	SDL_RendererFlip flip;

	SDL_Point* getPoint() {
		return &point;
	}
};