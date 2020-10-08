#include <SDL.h>

struct Alignment
{
private:
	SDL_Point point;
public:
	int x, y;
	int* x_internal;
	int* y_internal;
	double theta;

	SDL_Point* getPoint();
};