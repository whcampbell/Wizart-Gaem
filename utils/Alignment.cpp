#include "SDL.h"

struct Alignment
{
private:
	SDL_Point point;
public:
	int x, y;
	int* x_internal = &point.x;
	int* y_internal = &point.y;
	double theta;
	SDL_RendererFlip flip;

	SDL_Point* getPoint() {
		return &point;
	}
};