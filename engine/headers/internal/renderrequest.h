#pragma once
#include "sprite.h"

enum RenderType {
    REQ_IMAGE, REQ_SPRITE, REQ_TEXT, REQ_RECT, REQ_FRECT
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
    int frame;
    float scale;
    Texture* texture;
};

struct SpriteRequest {
    int z;
    RenderType type;
    int y;
    int x, w, h;
    int frame;
    float scale;
    double theta;
    SDL_Point point;
    SDL_RendererFlip flip;
    Texture* texture;
};

struct RectRequest {
    int z;
    RenderType type;
    int y;
    int x, w, h;
    float scale;
    SDL_Color color1, color2;
};

struct TextRequest {
    int z;
    RenderType type;
    int y;
    int x, w, h;
    float scale;
    double theta;
    SDL_Point point;
    SDL_RendererFlip flip;
    SDL_Texture* texture;
};

union RenderRequest {
    RenderRequest() {} 
    ~RenderRequest() {} 
    int z;
    Request request;
    ImageRequest image;
    SpriteRequest sprite;
    TextRequest text;
    RectRequest rect;
};

void drawRequest(RenderRequest* request);

void initRequestSystem();