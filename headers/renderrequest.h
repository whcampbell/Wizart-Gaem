#pragma once
#include "sprite.h"

extern SDL_sem* textsync;

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

struct TextRequest {
    int z;
    RenderType type;
    int y;
    int x, w, h;
    float scale;
    double theta;
    SDL_Point point;
    SDL_RendererFlip flip;
    bool* valid;
    int* reading;
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
};

void drawRequest(RenderRequest* request);

void initRequestSystem();