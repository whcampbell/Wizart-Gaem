#include "sprite.h"

enum RenderType {
    REQ_IMAGE, REQ_SPRITE, REQ_TEXT
};

struct Request {
    int z;
    RenderType type;
    int y;
};

struct ImageRequest {
    int z;
    RenderType type;
    int y;
    int x, w, h;
    Texture* texture;
    int frame;
    float scale;
};

struct SpriteRequest {
    int z;
    RenderType type;
    int y;
    int x, w, h;
    Texture* texture;
    int frame;
    float scale;
    double theta;
    SDL_Point point;
    SDL_RendererFlip flip;
};

struct TextRequest {
    int z;
    RenderType type;
    int y;
};

union RenderRequest {
    int z;
    Request request;
    ImageRequest image;
    SpriteRequest sprite;
    TextRequest text;
};

void drawRequest(RenderRequest request);