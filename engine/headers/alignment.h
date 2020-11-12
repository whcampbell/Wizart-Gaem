#pragma once
#include <SDL.h>
#include "vec.h"

/**
 * Contains data representing position and orientation
 */
struct Alignment
{
private:
	SDL_Point point;
public:
	Vector2 pos;
	int* x_internal = &point.x;
	int* y_internal = &point.y;
	double theta;
	SDL_RendererFlip flip;

	/**
 	* Returns the internal point of this alignment
 	*/
	SDL_Point* getPoint() {
		return &point;
	}
};