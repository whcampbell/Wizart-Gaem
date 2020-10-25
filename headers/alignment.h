#pragma once
#include <SDL.h>
#include "vector.h"

/**
 * Contains data representing position and orientation
 */
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

	/**
 	* Returns the internal point of this alignment
 	*/
	SDL_Point* getPoint() {
		return &point;
	}
};